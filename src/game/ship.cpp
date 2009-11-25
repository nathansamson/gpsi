#include "ship.h"

namespace SI {

	/**
	 * Public constructor.
	 *
	 * @param driver The driver for the ship. The ship manages the driver, 
	 *        so the driver will be freed when the ship is descructed.
	*/
	Ship::Ship(VShipDriver* driver): fShipDriver(driver) {
		fShipDriver->bind(this);
	}
	
	/**
	 * Descructor.
	*/
	Ship::~Ship() {
		delete fShipDriver;
	}
	
	/**
	 * Updates the state of the ship.
	 *
	 * @param ticks The number of ticks passed since the last update.
	*/
	void Ship::update(int ticks) {
		if (ticks < 0) {
			throw -ticks;
		}
		fShipDriver->update(ticks);
	}
}
