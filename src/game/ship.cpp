#include "ship.h"

namespace SI {
	Ship::Ship(VShipDriver* driver): fShipDriver(driver) {
		fShipDriver->bind(this);
	}
	
	Ship::~Ship() {
		delete fShipDriver;
	}
	
	void Ship::update(int ticks) {
		if (ticks < 0) {
			throw -ticks;
		}
		fShipDriver->update(ticks);
	}
}
