#include "game/gameentity.h"
#include "game/gameentityfactory.h"
#include "game/weapons/clusterbombcannon.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param ticksBetweenFire Minimum time between two shots.
	 * @param fac The entity factory.
	 * @param type The type of the clusterbomb.
	*/
	ClusterBombCannon::ClusterBombCannon(int ticksBetweenFire, IGameEntityFactory* fac, ClusterBombType* type):
	        VWeapon(ticksBetweenFire, fac), fBombType(type) {
	}
	
	/**
	 * Constructor.
	 *
	 * @param cannon The original cannon.
	 * @param ship The ship
	*/
	ClusterBombCannon::ClusterBombCannon(const ClusterBombCannon& cannon, Ship* ship):
	        VWeapon(cannon, ship), fBombType(cannon.fBombType) {
	}
	
	/**
	 * Create a new clusterbomb that is attachted to a ship.
	 *
	 * @param ship The ship
	 *
	 * @return A new cannon that can fire.
	*/
	ClusterBombCannon* ClusterBombCannon::addWeaponToShip(Ship* ship) {
		return new ClusterBombCannon(*this, ship);
	}
	
	/**
	 * Fire
	 *
	 * @return A cluster bomb.
	*/ 
	VGameEntity* ClusterBombCannon::fire() {
		if (canFire()) {
			resetTime();
			return fEntityFactory->createClusterBomb(fShip->getPosition(), fShip->getDirection(), fShip->getGroup(), fBombType);
		} else {
			return 0;
		}
	}
}
