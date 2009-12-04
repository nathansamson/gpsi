#ifndef INC_TEST_H
#define INC_TEST_H

#include <vector>

#include "game/shipdriver.h"
#include "game/ship.h"
#include "game/gameentityfactory.h"
#include "game/enemydriverfactory.h"

namespace SITest {
	#define SITEST_ASSERT_VECTORS_EQUAL(e, a)  CPPUNIT_ASSERT_DOUBLES_EQUAL(e.getX(), a.getX(), 1E-10);\
	                                           CPPUNIT_ASSERT_DOUBLES_EQUAL(e.getY(), a.getY(), 1E-10)

	#define MAGIC_FIRE_TICK 1349

	class MockShipDriver: public SI::VShipDriver {
	public:
		virtual void update(int ticks);
	};
	
	class MockShip: public SI::Ship {
	public:
		MockShip(SI::VShipDriver*, SI::Vector2, SI::IGameEntityFactory*);
		
		virtual void visualize();
		bool fVisualized;
	};
	
	class MockBullet: public SI::Bullet {
	public:
		MockBullet(SI::Vector2, SI::Vector2, SI::IGameEntityFactory*);
		
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
		SI::Bullet* createBullet(SI::Vector2, SI::Vector2);
		
		std::vector<MockShip*> fShips;
		std::vector<MockBullet*> fBullets;
	};
}

#endif // INC_TEST_H
