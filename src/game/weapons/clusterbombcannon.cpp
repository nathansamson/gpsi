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
	ClusterBombCannonBlueprint::ClusterBombCannonBlueprint(int ticksBetweenFire, IGameEntityFactory* fac, ClusterBombType* type):
	        VWeaponBlueprint(ticksBetweenFire, fac), fBombType(type) {
	}
	
	/**
	 * Create a new clusterbomb that is attachted to a ship.
	 *
	 * @param ship The ship
	 *
	 * @return A new cannon that can fire.
	*/
	ClusterBombCannon* ClusterBombCannonBlueprint::attachWeaponToShip(Ship* ship) {
		return new ClusterBombCannon(*this, ship);
	}
	
	/**
	 * Constructor.
	 *
	 * @param blueprint The blueprint of the cannon.
	 * @param ship The ship
	*/
	ClusterBombCannon::ClusterBombCannon(const ClusterBombCannonBlueprint& blueprint, Ship* ship):
	        VWeapon(blueprint, ship), fBombType(blueprint.fBombType) {
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
