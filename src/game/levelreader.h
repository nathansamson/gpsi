#ifndef INC_LEVELREADER_H
#define INC_LEVELREADER_H

#include <string>
#include <vector>

#include "tinyxml/tinyxml.h"
#include "game/gameentityfactory.h"
#include "game/enemydriverfactory.h"

namespace SI {
	class LevelReader {
	public:
		LevelReader(std::string, IGameEntityFactory*, EntityGroup*, IEnemyDriverFactory*);
		~LevelReader() {}
		
		std::vector<Ship*> getShips();
	private:
		TiXmlDocument fLevel;
		IGameEntityFactory* fEntityFactory;
		EntityGroup* fEnemyGroup;
		IEnemyDriverFactory* fEnemyDriverFactory;
	};
}

#endif // INC_LEVELREADER_H
