/** \file
 * File for the weaponery (weapon depot).
 *
 * @author Nathan Samson
*/

#include "game/weaponery.h"

namespace SI {
	/**
	 * Public destructor.
	*/
	Weaponery::~Weaponery() {
		clear();
	}
	
	/**
	 * Clear all weapons in the Weaponery.
	*/
	void Weaponery::clear() {
		for (std::map<std::string, VWeaponBlueprint*>::iterator it = fWeapons.begin(); it != fWeapons.end(); it++) {
			delete (*it).second;
		}
		fWeapons.clear();
		
		for (std::map<std::string, AmmoType*>::iterator it = fAmmo.begin(); it != fAmmo.end(); it++) {
			delete (*it).second;
		}
		fAmmo.clear();
	}

	/**
	 * Creates a weapon with a specific type for a specific ship.
	 *
	 * @param id The ID of the weapon.
	 * @param ship The ship of the weapon.
	 *
	 * @return A new weapon, the ship will own the weapon.
	*/
	VWeapon* Weaponery::getWeapon(std::string id, Ship* ship) {
		return fWeapons[id]->attachWeaponToShip(ship);
	}

	/**
	 * Insert a new type of ammo in the ammo list.
	 *
	 * @param id The unique id of the ammo.
	 * @param ammo The ammo type itself. This class owns the ammo.
	*/
	void Weaponery::addAmmo(std::string id, AmmoType* ammo) {
		fAmmo[id] = ammo;
	}

	/**
	 * Add a new weapon.
	 *
	 * @param id The ID of the weapon.
	 * @param weapon The blueprint of the weapon. This function owns the weapon. 
	*/
	void Weaponery::addWeapon(std::string id, VWeaponBlueprint* weapon) {
		fWeapons[id] = weapon;
	}
}
