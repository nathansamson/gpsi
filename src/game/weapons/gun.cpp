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
	Gun::Gun(int ticksBetweenFire, IGameEntityFactory* fac, Vector2 offset, BulletType* type):
	     VWeapon(ticksBetweenFire, fac), fBulletType(type), fOffset(-offset) {
	}
	
	/**
	 * Constructor.
	 *
	 * @param gun THe gun blueprint.
	 * @param ship The ship.
	*/
	Gun::Gun(const Gun& gun, Ship* ship): VWeapon(gun, ship),
	     fBulletType(gun.fBulletType), fOffset(gun.fOffset) {
	}
	
	Gun::~Gun() {
	}
	
	/**
	 * Attach the weapon to the ship.
	 *
	 * @param ship The ship.
	 *
	 * @return A Gun.
	*/
	Gun* Gun::addWeaponToShip(Ship* ship) {
		if (isBlueprint()) {
			return new Gun(*this, ship);
		} else {
			return 0;
		}
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
