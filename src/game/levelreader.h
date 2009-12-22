#ifndef INC_LEVELREADER_H
#define INC_LEVELREADER_H

#include <string>
#include <map>
#include <vector>

#include "tinyxml/ticpp.h"
#include "game/gameentityfactory.h"
#include "game/driverfactory.h"
#include "game/weaponery.h"

namespace SI {
	class LevelReader {
	public:
		LevelReader(std::string, IGameEntityFactory*, IDriverFactory*, Weaponery*);
		~LevelReader();
		
		std::vector<Ship*> getEnemyShips(EntityGroup*);
		Ship* getUserShip(EntityGroup*);
		std::string getLevelName();
		std::string getNextLevel();
	private:
		Vector2 parseVector(ticpp::Element*);
		static void parseBoundingShape(IBoundingShapeDescription*&, ticpp::Element*);
		void parseAmmo();
		void parseWeapons();
		std::map<std::string, ShipType> parseShipTypes();

		ticpp::Document fLevel;
		IGameEntityFactory* fEntityFactory;
		IDriverFactory* fDriverFactory;
		Weaponery* fWeaponery;
		std::map<std::string, ShipType> fShipTypes;
	};
}

#endif // INC_LEVELREADER_H
