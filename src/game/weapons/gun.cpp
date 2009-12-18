#include "game/weapons/gun.h"

namespace SI {
	Gun::Gun(int ticksBetweenFire, IGameEntityFactory* fac, Vector2 offset, BulletType* type):
	     VWeapon(ticksBetweenFire, fac), fBulletType(type), fOffset(-offset) {
	}
	
	Gun::Gun(const Gun& gun, Ship* ship): VWeapon(gun, ship),
	     fBulletType(gun.fBulletType), fOffset(gun.fOffset) {
	}
	
	Gun* Gun::addWeaponToShip(Ship* ship) {
		if (isBlueprint()) {
			return new Gun(*this, ship);
		} else {
			return 0;
		}
	}
	
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
