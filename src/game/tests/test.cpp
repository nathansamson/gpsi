#include "misc/vector2.h"
#include "test.h"

namespace SITest {
	void MockShipDriver::update(int ticks) {
		move(SI::Vector2(1.0/100, 0) * ticks);
	}
	
	SI::Ship* MockGameEntityFactory::createShip(SI::VShipDriver* driver, SI::Vector2 v) {
		MockShip* fCreatedShip = new MockShip(driver, v);
		fShips.push_back(fCreatedShip);
		return fCreatedShip;
	}
	
	MockShip::MockShip(SI::VShipDriver* driver, SI::Vector2 v): SI::Ship(driver, v), fVisualized(false) {
	}
	
	void MockShip::visualize() {
		fVisualized = true;
	}
	
	MockShipDriver* MockEnemyDriverFactory::createEnemyDriver() {
		MockShipDriver* driver = new MockShipDriver();
		fDrivers.push_back(driver);
		return driver;
	}
}
