#include "game/weapons/gun.h"

namespace SI {
	Gun::Gun(int ticksBetweenFire, IGameEntityFactory* fac, Ship* ship, Vector2 offset, BulletType type):
	     VWeapon(ticksBetweenFire, fac, ship), fBulletType(type), fOffset(-offset) {
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
