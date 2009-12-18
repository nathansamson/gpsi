#include "game/weapons/weapon.h"

namespace SI {
	VWeapon::VWeapon(int ticksBetweenFire, IGameEntityFactory* entityFactory):
	         fEntityFactory(entityFactory), fShip(0),
	         fTicksBetweenFire(ticksBetweenFire),
	         fTicksSinceLastFire(ticksBetweenFire) {
	}
	
	VWeapon::VWeapon(const VWeapon& weapon, Ship* ship):
	         fEntityFactory(weapon.fEntityFactory), fShip(ship),
	         fTicksBetweenFire(weapon.fTicksBetweenFire),
	         fTicksSinceLastFire(weapon.fTicksBetweenFire) {
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
	
	bool VWeapon::isBlueprint() {
		return fShip == 0;
	}
	
	/**
	 * Checks if the weapon is ready to fire.
	 *
	 * @return True if the weapon can fire.
	*/
	bool VWeapon::canFire() {
		return (!isBlueprint() && fTicksSinceLastFire >= fTicksBetweenFire);
	}
	
	/**
	 * Resets the reload time of the gun.
	*/
	void VWeapon::resetTime() {
		fTicksSinceLastFire = 0;
	}
	
	
}
