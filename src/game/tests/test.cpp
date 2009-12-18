#include "misc/vector2.h"
#include "test.h"

namespace SITest {
	void MockShipDriver::update(int ticks) {
		move(SI::Vector2(1.0/100, 0) * ticks);
		if (ticks == MAGIC_FIRE_TICK) {
			fire();
		}
	}
	
	void PeaceMockShipDriver::update(int ticks) {
	}
	
	void DeadlyMockShipDriver::update(int ticks) {
		fire();
	}
	
	SI::Ship* MockGameEntityFactory::createShip(SI::VShipDriver* driver,
	                                 SI::Vector2 v, int d, SI::EntityGroup* g,
	                                 SI::Weaponery* w, SI::ShipType t) {
		MockShip* fCreatedShip = new MockShip(driver, v, d, g, w, t, this);
		fShips.push_back(fCreatedShip);
		return fCreatedShip;
	}
	
	SI::Bullet* MockGameEntityFactory::createBullet(SI::Vector2 pos, int d,
	                                   SI::EntityGroup* g, SI::BulletType* t) {
		MockBullet* createdBullet = new MockBullet(pos, d, g, t, this);
		fBullets.push_back(createdBullet);
		return createdBullet;
	}
	
	MockShip::MockShip(SI::VShipDriver* driver, SI::Vector2 v, int d,
	                   SI::EntityGroup* g, SI::Weaponery* w, SI::ShipType t, SI::IGameEntityFactory* f):
	          SI::Ship(driver, v, d, g, t, f, w), fVisualized(false) {
	}
	
	void MockShip::visualize() {
		fVisualized = true;
	}
	
	MockBullet::MockBullet(SI::Vector2 pos, int d, SI::EntityGroup* g,
	                       SI::BulletType* t, SI::IGameEntityFactory* f): 
	            SI::Bullet(pos, d, g, t, f), fVisualized(false) {
	}
	
	void MockBullet::visualize() {
		fVisualized = true;
	}
	
	SI::VShipDriver* TestEnemyDriverFactory::createEnemyDriver(std::string name) {
		SI::VShipDriver* driver;
		if (name == "mockdriver") {
			driver = new MockShipDriver();
		} else if (name == "peacedriver") {
			driver = new PeaceMockShipDriver();
		} else if (name == "deadlydriver") {
			driver = new DeadlyMockShipDriver();
		} else {
			driver = SI::BuiltinEnemyDriverFactory::createEnemyDriver(name);
		}
		fDrivers.push_back(driver);
		return driver;
	}
}
