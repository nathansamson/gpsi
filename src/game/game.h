#ifndef INC_GAME_H
#define INC_GAME_H

#include <list>
#include "gameentityfactory.h"
#include "shipdriver.h"

namespace SI {
	class Game {
	public:
		Game(VShipDriver*, IGameEntityFactory*);
		
		void update(int);
	private:
		std::list<VGameEntity*> fEntities;
		IGameEntityFactory* fEntityFactory;
	};
}

#endif // INC_GAME_H
