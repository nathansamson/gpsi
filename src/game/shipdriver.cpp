#include "shipdriver.h"

namespace SI {

	/**
	 * Public constructor.
	*/
	VShipDriver::VShipDriver(): fEntity(0) {
	}
	
	/**
	 * Binds the driver to a specific ship.
	 *
	 * @param e The ship to drive.
	*/
	void VShipDriver::bind(Ship* e) {
		fEntity = e;
	}
	
	/**
	 * Moves the ship with the specified offset.
	 *
	 * @param v The offset of the movement.
	*/
	void VShipDriver::move(Vector2 v) {
		fEntity->move(v);
	}
	
	/**
	 * Fire a weapon.
	*/
	void VShipDriver::fire() {
		fEntity->fire();
	}
}
