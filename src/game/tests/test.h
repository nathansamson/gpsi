#ifndef INC_TEST_H
#define INC_TEST_H

#include "game/shipdriver.h"
#include "game/ship.h"
#include "game/gameentityfactory.h"

namespace SITest {
	class MockShipDriver: public SI::VShipDriver {
	public:
		virtual void update(int ticks);
	};
	
	class MockShip: public SI::Ship {
	public:
		MockShip(SI::VShipDriver*);
		
		virtual void visualize();
		bool fVisualized;
	};
	
	class MockGameEntityFactory: public SI::IGameEntityFactory {
	public:
		SI::Ship* createShip(SI::VShipDriver*);
		MockShip* fCreatedShip;
	};
}

#endif // INC_TEST_H
