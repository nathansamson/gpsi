#include "misc/vector2.h"
#include "test.h"

namespace SITest {
	void MockShipDriver::update(int ticks) {
		move(SI::Vector2(1.0/100, 0) * ticks);
	}
	
	SI::Ship* MockGameEntityFactory::createShip(SI::VShipDriver* driver) {
		fCreatedShip = new MockShip(driver);
		return fCreatedShip;
	}
	
	MockShip::MockShip(SI::VShipDriver* driver): SI::Ship(driver), fVisualized(false) {
	}
	
	void MockShip::visualize() {
		fVisualized = true;
	}
}
