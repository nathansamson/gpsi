#ifndef INC_LEVELREADER_H
#define INC_LEVELREADER_H

#include <string>
#include <map>
#include <vector>

#include "tinyxml/ticpp.h"
#include "game/gameentityfactory.h"
#include "game/enemydriverfactory.h"
#include "game/weaponery.h"

namespace SI {
	class LevelReader {
	public:
		LevelReader(std::string, IGameEntityFactory*, IEnemyDriverFactory*, Weaponery*);
		~LevelReader();
		
		std::vector<Ship*> getEnemyShips(EntityGroup*);
		Ship* getUserShip(VShipDriver*, EntityGroup*);
	private:
		static void parseBoundingShape(IBoundingShapeDescription*&, ticpp::Element*);
		void parseAmmo();
		void parseWeapons();
		std::map<std::string, ShipType> parseShipTypes();

		ticpp::Document fLevel;
		IGameEntityFactory* fEntityFactory;
		IEnemyDriverFactory* fEnemyDriverFactory;
		Weaponery* fWeaponery;
		std::map<std::string, ShipType> fShipTypes;
	};
}

#endif // INC_LEVELREADER_H
