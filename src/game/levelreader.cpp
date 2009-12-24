#include <map>

#include "game/levelreader.h"
#include "game/ship.h"
#include "game/synchronousdriver.h"
#include "game/weapons/gun.h"
#include "game/weapons/clusterbombcannon.h"
#include "misc/boundingbox.h"

namespace SI {
	/**
	 * Constructor
	 *
	 * @param fileName The full filename.
	 * @param fac The entity factory.
	 * @param driverFactory The driver factory;
	 * @param weaponery The weaponery
	*/
	LevelReader::LevelReader(std::string fileName, IGameEntityFactory* fac,
	                         IDriverFactory* driverFactory,
	                         Weaponery* weaponery):
	             fLevel(fileName.c_str()), fEntityFactory(fac),
	             fDriverFactory(driverFactory),
	             fWeaponery(weaponery) {
		fLevel.LoadFile();
		
		parseAmmo();
		parseWeapons();
		fShipTypes = parseShipTypes();
	}
	
	/**
	 * Desctructor.
	*/
	LevelReader::~LevelReader() {
		for (std::map<std::string, ShipType>::iterator it = fShipTypes.begin(); it != fShipTypes.end(); it++) {
			delete (*it).second.fBoundingShapeDesc;
		}
	}
	
	/**
	 * Parse bounding shape.
	 *
	 * @param shape The resulting shape.
	 * @param boundingshape The element to parse.
	*/
	void LevelReader::parseBoundingShape(IBoundingShapeDescription*& shape,
	                                     ticpp::Element* boundingshape) {
		if (boundingshape->GetAttribute("type") == "boundingbox") {
			double w = boundingshape->GetAttribute<double>("w");
			double h = boundingshape->GetAttribute<double>("h");
			shape = new BoundingBoxDescription(w, h);
		} else {
			throw 666;
		}
	}
	
	/**
	 * Parse the ammo list.
	*/
	void LevelReader::parseAmmo() {
		ticpp::Element* ammoNode = fLevel.FirstChild("level")->FirstChild("ammo")->ToElement();
		
		
		{// Bullets
			ticpp::Iterator<ticpp::Element> bulletNode("bullet");
			for (bulletNode = bulletNode.begin(ammoNode); bulletNode != bulletNode.end(); bulletNode++) {
				BulletType* bullet = new BulletType();
				parseBoundingShape(bullet->fBoundingShapeDesc,
					               bulletNode->FirstChild("boundingshape")->ToElement());
				double ySpeed;
				bulletNode->FirstChild("speed")->ToElement()->GetText(&ySpeed);
				bullet->fSpeed = Vector2(0.0, ySpeed);
				fWeaponery->addAmmo(bulletNode->GetAttribute("id"), bullet);
			}
		}
		
		{
			// Cluster bombs
			ticpp::Iterator<ticpp::Element> clusterNode("clusterbomb");
			for (clusterNode = clusterNode.begin(ammoNode); clusterNode != clusterNode.end(); clusterNode++) {
				ClusterBombType* cluster = new ClusterBombType();
				parseBoundingShape(cluster->fBoundingShapeDesc,
					               clusterNode->FirstChild("boundingshape")->ToElement());
				double ySpeed;
				clusterNode->FirstChild("speed")->ToElement()->GetText(&ySpeed);
				cluster->fSpeed = Vector2(0.0, ySpeed);
				clusterNode->FirstChild("maxticksalive")->ToElement()->GetText(&cluster->fMaxTicksAlive);
				
				clusterNode->FirstChild("bullets")->ToElement()->GetText(&cluster->fBullets);
				cluster->fBulletType = fWeaponery->getAmmoType<BulletType>(
				                         clusterNode->FirstChild("bullet-type")
				                                    ->ToElement()->GetText());
				
				fWeaponery->addAmmo(clusterNode->GetAttribute("id"), cluster);
			}
		}
	}
	
	/**
	 * Parse the weapon list.
	*/
	void LevelReader::parseWeapons() {
		ticpp::Element* weaponsNode = fLevel.FirstChild("level")->FirstChild("weapons")->ToElement();
		ticpp::Iterator<ticpp::Element> weaponNode("weapon");
		for (weaponNode = weaponNode.begin(weaponsNode); weaponNode != weaponNode.end(); weaponNode++) {
			VWeaponBlueprint* weapon = 0;
			std::string weaponType = weaponNode->GetAttribute("type");
			if (weaponType == "gun") {
				int coolingOffTime;
				weaponNode->FirstChild("coolingofftime")->ToElement()->GetText(&coolingOffTime);
				double xOffset;
				weaponNode->FirstChild("xoffset")->ToElement()->GetText(&xOffset);
				BulletType* bullet = fWeaponery->getAmmoType<BulletType>(
				                     weaponNode->FirstChild("ammo")
				                               ->ToElement()->GetText());
				weapon = new GunBlueprint(coolingOffTime, fEntityFactory,
				                 Vector2(xOffset, 0.0), bullet);
			} else if (weaponType == "cluster-bomb-cannon") {
				int coolingOffTime;
				weaponNode->FirstChild("coolingofftime")->ToElement()->GetText(&coolingOffTime);
				
				ClusterBombType* ammo = fWeaponery->getAmmoType<ClusterBombType>(
				                             weaponNode->FirstChild("ammo")
				                                       ->ToElement()->GetText());
				weapon = new ClusterBombCannonBlueprint(coolingOffTime, fEntityFactory, ammo);
			}
			fWeaponery->addWeapon(weaponNode->GetAttribute("id"), weapon);
		}
	}

	/**
	 * Parse the ship types.
	 *
	 * @return A map with ID's and shiptypes.
	*/
	std::map<std::string, ShipType> LevelReader::parseShipTypes() {
		std::map<std::string, ShipType> shipTypes;
		ticpp::Element* shipsNode = fLevel.FirstChild("level")->FirstChild("ships")->ToElement();
		ticpp::Iterator<ticpp::Element> shipTypeNode("ship");
		for (shipTypeNode = shipTypeNode.begin(shipsNode); shipTypeNode != shipTypeNode.end(); shipTypeNode++) {
			ShipType shipType;
			shipType.fName = (*shipTypeNode).GetAttribute("name");
			ticpp::Element* boundingshape = (*shipTypeNode).FirstChild("boundingshape")->ToElement();
			parseBoundingShape(shipType.fBoundingShapeDesc, boundingshape);
			
			ticpp::Element* weaponsNode = shipTypeNode->FirstChild("weapons")->ToElement();
			ticpp::Iterator<ticpp::Element> weaponNode("weapon");
			for (weaponNode = weaponNode.begin(weaponsNode); weaponNode != weaponNode.end(); weaponNode++) {
				shipType.fWeapons.push_back(weaponNode->GetAttribute("name"));
			}
			shipType.fMaxSpeed = parseVector(shipTypeNode->FirstChild("maxspeed")->ToElement());
			shipType.fMaxAbsSpeedDiff = parseVector(shipTypeNode->FirstChild("maxspeeddiff")->ToElement());
			shipType.fHitPoints = shipTypeNode->GetAttribute<int>("hitpoints");
			
			shipTypes[shipType.fName] = shipType;
		}
		return shipTypes;
	}

	/**
	 * Parse a a vector
	 *
	 * @param vectorNode The vector node.
	 *
	 * @return The vector
	*/
	Vector2 LevelReader::parseVector(ticpp::Element* vectorNode) {
		Vector2 vector;
		vector.setX(vectorNode->GetAttribute<double>("x"));
		vector.setY(vectorNode->GetAttribute<double>("y"));
		return vector;
	}

	/**
	 * Returns a list of enemy ships in this level.
	 *
	 * @param enemyGroup The enemy group.
	 *
	 * @return A list of enemy ships.
	*/
	std::vector<Ship*> LevelReader::getEnemyShips(EntityGroup* enemyGroup) {
		std::vector<Ship*> enemies;
		ticpp::Element* enemiesNode = fLevel.FirstChild("level")->FirstChild("enemies")->ToElement();
		ticpp::Iterator<ticpp::Element> rowElement("row");
		for (rowElement = rowElement.begin(enemiesNode); rowElement != rowElement.end(); rowElement++) {
			ShipType shipType = fShipTypes[rowElement->GetAttribute("shiptype")];
			int count = rowElement->GetAttribute<int>("count");
			double margin = rowElement->GetAttribute<double>("margin");
			std::string align = rowElement->GetAttribute("align");
			double y = rowElement->GetAttribute<double>("y");
			
			for (int i = 1; i <= count; i++) {
				Vector2 pos;
				double offset;
				if (align == "center") {
					offset = 0.0;
				} else {
					offset = rowElement->GetAttribute<double>("align");
				}
				pos = Vector2(i*(8.0-2*margin)/(count+1) + offset -4.0 + margin, y);
				
				ticpp::Iterator<ticpp::Attribute> attribute;
				std::map<std::string, std::string> attributeMap;
				for(attribute = attribute.begin(rowElement.Get()); attribute != attribute.end(); attribute++) {
					attributeMap[(*attribute).Name()] = (*attribute).Value();
				}
				enemies.push_back(fEntityFactory->createAIShip(
				                     fDriverFactory->createEnemyDriver(
				                         rowElement->GetAttribute("driver"), attributeMap),
				                         pos, 180, enemyGroup, fWeaponery,
				                         shipType));
			}
		}
		return enemies;
	}
	
	/**
	 * Returns the user ship of the level
	 *
	 * @param userGroup The group of the user.
	 *
	 * @return The user ship.
	*/
	Ship* LevelReader::getUserShip(EntityGroup* userGroup) {
		ticpp::Element* shipNode = fLevel.FirstChild("level")->FirstChild("usership")->ToElement();
		ShipType shipType = fShipTypes[shipNode->GetAttribute("shiptype")];
		return fEntityFactory->createUserShip(fDriverFactory->createUserDriver(),
				                         Vector2(0, -2.0), 0, userGroup, fWeaponery,
				                         shipType);
	}
	
	/**
	 * Returns the name of the level.
	 *
	 * @return The name of the level.
	*/
	std::string LevelReader::getLevelName() {
		return fLevel.FirstChild("level")->FirstChild("name")->ToElement()->GetText();
	}

	/**
	 * Returns the filename of the next level.
	 *
	 * @return Filename of the next level or the empty string if their is no next level.
	*/	
	std::string LevelReader::getNextLevel() {
		try {
			return fLevel.FirstChild("level")->FirstChild("next")->ToElement()->GetText();
		} catch (...) {
			return "";
		}
	}
}
