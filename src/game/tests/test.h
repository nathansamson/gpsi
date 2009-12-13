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

	#define MAGIC_FIRE_TICK 235

	class MockShipDriver: public SI::VShipDriver {
	public:
		virtual void update(int ticks);
	};
	
	class PeaceMockShipDriver: public SI::VShipDriver {
	public:
		virtual void update(int ticks);
	};
	
	class DeadlyMockShipDriver: public SI::VShipDriver {
	public:
		virtual void update(int ticks);
	};
	
	class MockShip: public SI::Ship {
	public:
		MockShip(SI::VShipDriver*, SI::Vector2, int, SI::EntityGroup*, SI::ShipType, SI::IGameEntityFactory*);
		
		virtual void visualize();
		bool fVisualized;
	};
	
	class MockBullet: public SI::Bullet {
	public:
		MockBullet(SI::Vector2, int, SI::EntityGroup*, SI::BulletType, SI::IGameEntityFactory*);
		
		virtual void visualize();
		bool fVisualized;
	};
	
	class MockEnemyDriverFactory: public SI::IEnemyDriverFactory {
	public:
		virtual MockShipDriver* createEnemyDriver();
		std::vector<SI::VShipDriver*> fDrivers;
	};
	
	class PeaceMockEnemyDriverFactory: public SI::IEnemyDriverFactory {
	public:
		virtual PeaceMockShipDriver* createEnemyDriver();
	};
	
	class DeadlyMockEnemyDriverFactory: public SI::IEnemyDriverFactory {
	public:
		virtual DeadlyMockShipDriver* createEnemyDriver();
	};
	
	class MockGameEntityFactory: public SI::IGameEntityFactory {
	public:
		SI::Ship* createShip(SI::VShipDriver*, SI::Vector2, int, SI::EntityGroup*, SI::ShipType);	
		SI::Bullet* createBullet(SI::Vector2, int, SI::EntityGroup*, SI::BulletType);
		
		std::vector<MockShip*> fShips;
		std::vector<MockBullet*> fBullets;
	};
}

#endif // INC_TEST_H
