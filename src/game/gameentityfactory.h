#ifndef INC_GAMEENTITYFACTORY_H
#define INC_GAMEENTITYFACTORY_H

#include "game/shipdriver.h"
#include "game/ship.h"

namespace SI {
	class IGameEntityFactory {
	public:
		virtual Ship* createShip(VShipDriver*) = 0;
	};
}

#endif // INC_GAMEENTITYFACTORY_H
