/** \file
 * File for the gun.
 *
 * @author Nathan Samson
*/

#include "game/weapons/gun.h"
#include "game/gameentity.h"
#include "game/gameentityfactory.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param ticksBetweenFire time between 2 shots.
	 * @param fac The entity factory.
	 * @param offset Offset to the ship.
	 * @param type The bullet type.
	*/
	GunBlueprint::GunBlueprint(int ticksBetweenFire, IGameEntityFactory* fac, Vector2 offset, BulletType* type):
	     VWeaponBlueprint(ticksBetweenFire, fac), fBulletType(type), fOffset(-offset) {
	}
	
	GunBlueprint::~GunBlueprint() {
	}
	
	/**
	 * Attach the weapon to the ship.
	 *
	 * @param ship The ship.
	 *
	 * @return A Gun.
	*/
	Gun* GunBlueprint::attachWeaponToShip(Ship* ship) {
		return new Gun(*this, ship);
	}
	
	/**
	 * Constructor.
	 *
	 * @param blueprint THe gun blueprint.
	 * @param ship The ship.
	*/
	Gun::Gun(const GunBlueprint& blueprint, Ship* ship): VWeapon(blueprint, ship),
	     fBulletType(blueprint.fBulletType), fOffset(blueprint.fOffset) {
	}
	
	Gun::~Gun() {
	}

	/**
	 * Fire a new bullet from the gun.
	 *
	 * @return The new bullet.
	*/	
	VGameEntity* Gun::fire() {
		if (canFire()) {
			fOffset *= -1;
			resetTime();
			return fEntityFactory->createBullet(fShip->getPosition() + fOffset, fShip->getDirection(), fShip->getGroup(), fBulletType);
		} else {
			return 0;
		}
	}
}
