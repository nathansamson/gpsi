#include <map>

#include "game/levelreader.h"
#include "game/ship.h"
#include "game/synchronousdriver.h"
#include "game/weapons/gun.h"
#include "game/weapons/clusterbombcannon.h"
#include "misc/boundingbox.h"

namespace SI {
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
	
	LevelReader::~LevelReader() {
		for (std::map<std::string, ShipType>::iterator it = fShipTypes.begin(); it != fShipTypes.end(); it++) {
			delete (*it).second.fBoundingShapeDesc;
		}
	}
	
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
	
	void LevelReader::parseWeapons() {
		ticpp::Element* weaponsNode = fLevel.FirstChild("level")->FirstChild("weapons")->ToElement();
		ticpp::Iterator<ticpp::Element> weaponNode("weapon");
		for (weaponNode = weaponNode.begin(weaponsNode); weaponNode != weaponNode.end(); weaponNode++) {
			VWeapon* weapon = 0;
			std::string weaponType = weaponNode->GetAttribute("type");
			if (weaponType == "gun") {
				int coolingOffTime;
				weaponNode->FirstChild("coolingofftime")->ToElement()->GetText(&coolingOffTime);
				double xOffset;
				weaponNode->FirstChild("xoffset")->ToElement()->GetText(&xOffset);
				BulletType* bullet = fWeaponery->getAmmoType<BulletType>(
				                     weaponNode->FirstChild("ammo")
				                               ->ToElement()->GetText());
				weapon = new Gun(coolingOffTime, fEntityFactory,
				                 Vector2(xOffset, 0.0), bullet);
			} else if (weaponType == "cluster-bomb-cannon") {
				int coolingOffTime;
				weaponNode->FirstChild("coolingofftime")->ToElement()->GetText(&coolingOffTime);
				
				ClusterBombType* ammo = fWeaponery->getAmmoType<ClusterBombType>(
				                             weaponNode->FirstChild("ammo")
				                                       ->ToElement()->GetText());
				weapon = new ClusterBombCannon(coolingOffTime, fEntityFactory, ammo);
			}
			fWeaponery->addWeapon(weaponNode->GetAttribute("id"), weapon);
		}
	}

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
			
			shipTypes[shipType.fName] = shipType;
		}
		return shipTypes;
	}

	Vector2 LevelReader::parseVector(ticpp::Element* vectorNode) {
		Vector2 vector;
		vector.setX(vectorNode->GetAttribute<double>("x"));
		vector.setY(vectorNode->GetAttribute<double>("y"));
		return vector;
	}

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
				
				enemies.push_back(fEntityFactory->createShip(
				                     fDriverFactory->createEnemyDriver(
				                         rowElement->GetAttribute("driver")),
				                         pos, 180, enemyGroup, fWeaponery,
				                         shipType));
			}
		}
		return enemies;
	}
	
	Ship* LevelReader::getUserShip(EntityGroup* userGroup) {
		ticpp::Element* shipNode = fLevel.FirstChild("level")->FirstChild("usership")->ToElement();
		ShipType shipType = fShipTypes[shipNode->GetAttribute("shiptype")];
		return fEntityFactory->createShip(fDriverFactory->createUserDriver(),
				                         Vector2(0, -2.0), 0, userGroup, fWeaponery,
				                         shipType);
	}
	
	std::string LevelReader::getLevelName() {
		return fLevel.FirstChild("level")->FirstChild("name")->ToElement()->GetText();
	}
	
	std::string LevelReader::getNextLevel() {
		try {
			return fLevel.FirstChild("level")->FirstChild("next")->ToElement()->GetText();
		} catch (...) {
			return "";
		}
	}
}
