#include "misc/vector2.h"
#include "test.h"

namespace SITest {
	void MockShipDriver::update(int ticks) {
		move(SI::Vector2(1.0/100, 0) * ticks);
		if (ticks == MAGIC_FIRE_TICK) {
			fire();
		}
	}
	
	SI::Ship* MockGameEntityFactory::createShip(SI::VShipDriver* driver, SI::Vector2 v) {
		MockShip* fCreatedShip = new MockShip(driver, v, this);
		fShips.push_back(fCreatedShip);
		return fCreatedShip;
	}
	
	SI::Bullet* MockGameEntityFactory::createBullet(SI::Vector2 s, SI::Vector2 pos) {
		MockBullet* createdBullet = new MockBullet(s, pos, this);
		fBullets.push_back(createdBullet);
		return createdBullet;
	}
	
	MockShip::MockShip(SI::VShipDriver* driver, SI::Vector2 v, SI::IGameEntityFactory* f): SI::Ship(driver, v, f), fVisualized(false) {
	}
	
	void MockShip::visualize() {
		fVisualized = true;
	}
	
	MockBullet::MockBullet(SI::Vector2 s, SI::Vector2 pos, SI::IGameEntityFactory* f): SI::Bullet(s, pos, f), fVisualized(false) {
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
