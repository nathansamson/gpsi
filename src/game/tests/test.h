#ifndef INC_TEST_H
#define INC_TEST_H

#include <vector>

#include "game/shipdriver.h"
#include "game/ship.h"
#include "game/gameentityfactory.h"
#include "game/builtindriverfactory.h"
#include "game/gamevisualizer.h"

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
		MockShip(SI::VShipDriver*, SI::Vector2, int, SI::EntityGroup*,
		         SI::Weaponery*, SI::ShipType, SI::IGameEntityFactory*);
		
		virtual void visualize();
		bool fVisualized;
	};
	
	class MockBullet: public SI::Bullet {
	public:
		MockBullet(SI::Vector2, int, SI::EntityGroup*, SI::BulletType*, SI::IGameEntityFactory*);
		
		virtual void visualize();
		bool fVisualized;
	};
	
	class TestDriverFactory: public SI::BuiltinDriverFactory {
	public:
		TestDriverFactory(std::string userType);
		virtual ~TestDriverFactory() {}
		
		virtual SI::VShipDriver* createUserDriver();
		virtual SI::VShipDriver* createEnemyDriver(std::string);
		std::vector<SI::VShipDriver*> fDrivers;
	private:
		std::string fType;
	};
	
	class MockGameEntityFactory: public SI::IGameEntityFactory {
	public:
		SI::Ship* createUserShip(SI::VShipDriver*, SI::Vector2, int, SI::EntityGroup*, SI::Weaponery*, SI::ShipType);	
		SI::Ship* createAIShip(SI::VShipDriver*, SI::Vector2, int, SI::EntityGroup*, SI::Weaponery*, SI::ShipType);	
		SI::Bullet* createBullet(SI::Vector2, int, SI::EntityGroup*, SI::BulletType*);
		SI::ClusterBomb* createClusterBomb(SI::Vector2, int, SI::EntityGroup*, SI::ClusterBombType*);
		
		std::vector<MockShip*> fShips;
		std::vector<MockBullet*> fBullets;
	};
	
	class MockGameVisualizer: public SI::IGameVisualizer {
		virtual void draw() {}
		virtual bool inNonGamePhase() { return false; }
		virtual void userDies() {}
		virtual void userWins() {}
		virtual void levelChange(std::string) {}
	};
}

#endif // INC_TEST_H
