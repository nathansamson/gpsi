#include "game/weapons/weapon.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param ticksBetweenFire ticks between fire.
	 * @param entityFactory The entity factory.
	*/
	VWeaponBlueprint::VWeaponBlueprint(int ticksBetweenFire, IGameEntityFactory* entityFactory):
	         fEntityFactory(entityFactory), fTicksBetweenFire(ticksBetweenFire) {
	}
	
	VWeaponBlueprint::~VWeaponBlueprint() {
	}

	/**
	 * Attach the weapon to a ship.
	 *
	 * @param blueprint The original weapon
	 * @param ship The ship.
	*/	
	VWeapon::VWeapon(const VWeaponBlueprint& blueprint, Ship* ship):
	         fShip(ship), fEntityFactory(blueprint.fEntityFactory),
	         fTicksBetweenFire(blueprint.fTicksBetweenFire),
	         fTicksSinceLastFire(blueprint.fTicksBetweenFire) {
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
