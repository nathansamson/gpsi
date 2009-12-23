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
	/**
	 * A level reader class.
	*/
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

		/**
		 * The TiCPP XML document.
		*/
		ticpp::Document fLevel;
		
		/**
		 * The entity factory.
		*/
		IGameEntityFactory* fEntityFactory;
		
		/**
		 * The driver factory.
		*/
		IDriverFactory* fDriverFactory;
		
		/**
		 * The weapon depot.
		*/
		Weaponery* fWeaponery;
		
		/**
		 * A map of ship types.
		*/
		std::map<std::string, ShipType> fShipTypes;
	};
}

#endif // INC_LEVELREADER_H
