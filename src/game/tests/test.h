#ifndef INC_TEST_H
#define INC_TEST_H

#include <vector>

#include "game/shipdriver.h"
#include "game/ship.h"
#include "game/gameentityfactory.h"
#include "game/enemydriverfactory.h"

namespace SITest {
	class MockShipDriver: public SI::VShipDriver {
	public:
		virtual void update(int ticks);
	};
	
	class MockShip: public SI::Ship {
	public:
		MockShip(SI::VShipDriver*, SI::Vector2);
		
		virtual void visualize();
		bool fVisualized;
	};
	
	class MockEnemyDriverFactory: public SI::IEnemyDriverFactory {
	public:
		virtual MockShipDriver* createEnemyDriver();
		std::vector<SI::VShipDriver*> fDrivers;
	};
	
	class MockGameEntityFactory: public SI::IGameEntityFactory {
	public:
		SI::Ship* createShip(SI::VShipDriver*, SI::Vector2);
		std::vector<MockShip*> fShips;
	};
}

#endif // INC_TEST_H
