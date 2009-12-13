#include <map>
#include "tinyxml/tinyxml.h"

#include "game/levelreader.h"
#include "game/ship.h"
#include "game/synchronousdriver.h"
#include "misc/boundingbox.h"

namespace SI {
	LevelReader::LevelReader(std::string fileName, IGameEntityFactory* fac,
	                         EntityGroup* enemyGroup, IEnemyDriverFactory* enemyDriverFactory):
	             fLevel(fileName.c_str()), fEntityFactory(fac),
	             fEnemyGroup(enemyGroup), fEnemyDriverFactory(enemyDriverFactory) {
		fLevel.LoadFile();
	}
	
	std::vector<Ship*> LevelReader::getShips() {
		std::map<std::string, ShipType> shipTypes;
		TiXmlNode* shipsNode = fLevel.RootElement()->FirstChild("ships");
		TiXmlNode* shipTypeNode = 0;
		while ((shipTypeNode = shipsNode->IterateChildren(shipTypeNode))) {
			if (shipTypeNode->Type() != TiXmlNode::ELEMENT) {
				continue;
			}
			if (strcmp("ship", shipTypeNode->Value()) == 0) {
				ShipType shipType;
				shipType.fName = shipTypeNode->ToElement()->Attribute("name");
				TiXmlElement* boundingshape = shipTypeNode->FirstChild("boundingshape")->ToElement();
				if (strcmp(boundingshape->Attribute("type"), "boundingbox") == 0) {
					double w;
					boundingshape->Attribute("w", &w);
					double h;
					boundingshape->Attribute("w", &h);
					shipType.fBoundingShapeDesc = new BoundingBoxDescription(w, h);
				} else {
					continue; // Silently skip;
				}
				shipTypes[shipType.fName] = shipType;
			}
		}

		std::vector<Ship*> enemies;
		TiXmlNode* enemiesNode = fLevel.RootElement()->FirstChild("enemies");
		TiXmlNode* rowNode = 0;
		while ((rowNode = enemiesNode->IterateChildren(rowNode))) {
			if (rowNode->Type() != TiXmlNode::ELEMENT) {
				continue;
			}
			TiXmlElement* rowElement = rowNode->ToElement();
			ShipType shipType = shipTypes[rowElement->Attribute("shiptype")];
			int count;
			rowElement->Attribute("count", &count);
			double margin;
			rowElement->Attribute("margin", &margin);
			std::string align = rowElement->Attribute("align");
			double y;
			rowElement->Attribute("y", &y);
			
			for (int i = 1; i <= count; i++) {
				Vector2 pos;
				double offset;
				if (align == "center") {
					offset = 0.0;
				} else {
					rowElement->Attribute("align", &offset);
				}
				pos = Vector2(i*(8.0-2*margin)/(count+1) + offset -4.0 + margin, y);
				
				enemies.push_back(fEntityFactory->createShip(fEnemyDriverFactory->createEnemyDriver(rowElement->Attribute("driver")), pos, 180, fEnemyGroup, shipType));
			}
		}
		
		for (std::map<std::string, ShipType>::iterator it = shipTypes.begin(); it != shipTypes.end(); it++) {
			delete (*it).second.fBoundingShapeDesc;
		}

		return enemies;
	}
}
