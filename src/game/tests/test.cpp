#include "misc/vector2.h"
#include "test.h"

namespace SITest {
	void MockShipDriver::update(int ticks) {
		move(SI::Vector2(1.0/100, 0) * ticks);
		if (ticks == MAGIC_FIRE_TICK) {
			fire();
		}
	}
	
	SI::Ship* MockGameEntityFactory::createShip(SI::VShipDriver* driver,
	                                 SI::Vector2 v, int d, SI::ShipType t) {
		MockShip* fCreatedShip = new MockShip(driver, v, d, t, this);
		fShips.push_back(fCreatedShip);
		return fCreatedShip;
	}
	
	SI::Bullet* MockGameEntityFactory::createBullet(SI::Vector2 pos, int d,
	                                   SI::BulletType t) {
		MockBullet* createdBullet = new MockBullet(pos, d, t, this);
		fBullets.push_back(createdBullet);
		return createdBullet;
	}
	
	MockShip::MockShip(SI::VShipDriver* driver, SI::Vector2 v, int d,
	                   SI::ShipType t, SI::IGameEntityFactory* f):
	          SI::Ship(driver, v, d, t, f), fVisualized(false) {
	}
	
	void MockShip::visualize() {
		fVisualized = true;
	}
	
	MockBullet::MockBullet(SI::Vector2 pos, int d,
	                       SI::BulletType t, SI::IGameEntityFactory* f): 
	            SI::Bullet(pos, d, t, f), fVisualized(false) {
	}
	
	void MockBullet::visualize() {
		fVisualized = true;
	}
	
	MockShipDriver* MockEnemyDriverFactory::createEnemyDriver() {
		MockShipDriver* driver = new MockShipDriver();
		fDrivers.push_back(driver);
		return driver;
	}
}
