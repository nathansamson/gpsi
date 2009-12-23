#include "game/weapons/weapon.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param ticksBetweenFire ticks between fire.
	 * @param entityFactory The entity factory.
	*/
	VWeapon::VWeapon(int ticksBetweenFire, IGameEntityFactory* entityFactory):
	         fEntityFactory(entityFactory), fShip(0),
	         fTicksBetweenFire(ticksBetweenFire),
	         fTicksSinceLastFire(ticksBetweenFire) {
	}

	/**
	 * Attach the weapon to a ship.
	 *
	 * @param weapon The original weapon
	 * @param ship The ship.
	*/	
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
	
	/**
	 * checks if the weapon is blueprint.
	*/
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
