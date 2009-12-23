#include "game/gameentity.h"
#include "game/gameentityfactory.h"
#include "game/weapons/clusterbombcannon.h"

namespace SI {
	ClusterBombCannon::ClusterBombCannon(int ticksBetweenFire, IGameEntityFactory* fac, ClusterBombType* type):
	        VWeapon(ticksBetweenFire, fac), fBombType(type) {
	}
	
	ClusterBombCannon::ClusterBombCannon(const ClusterBombCannon& cannon, Ship* ship):
	        VWeapon(cannon, ship), fBombType(cannon.fBombType) {
	}
	
	ClusterBombCannon* ClusterBombCannon::addWeaponToShip(Ship* ship) {
		return new ClusterBombCannon(*this, ship);
	}
	
	VGameEntity* ClusterBombCannon::fire() {
		if (canFire()) {
			resetTime();
			return fEntityFactory->createClusterBomb(fShip->getPosition(), fShip->getDirection(), fShip->getGroup(), fBombType);
		} else {
			return 0;
		}
	}
}
