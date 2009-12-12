#include "game/weapons/weapon.h"

namespace SI {
	VWeapon::VWeapon(int ticksBetweenFire, IGameEntityFactory* entityFactory, Ship* ship):
	         fEntityFactory(entityFactory), fShip(ship),
	         fTicksBetweenFire(ticksBetweenFire), fTicksSinceLastFire(ticksBetweenFire) {
	}
	
	/**
	 * Desctructor.
	*/
	VWeapon::~VWeapon() {
	}
	
	/**
	 * Update the state of the weapon.
	 *
	 * @param ticks Number of ticks passed since last update.
	*/
	void VWeapon::update(int ticks) {
		fTicksSinceLastFire += ticks;
	}
	
	/**
	 * Checks if the weapon is ready to fire.
	 *
	 * @return True if the weapon can fire.
	*/
	bool VWeapon::canFire() {
		return (fTicksSinceLastFire >= fTicksBetweenFire);
	}
	
	/**
	 * Resets the reload time of the gun.
	*/
	void VWeapon::resetTime() {
		fTicksSinceLastFire = 0;
	}
	
	
}
