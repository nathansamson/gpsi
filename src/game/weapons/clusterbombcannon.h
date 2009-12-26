#ifndef INC_CLUSTERBOMBCANNON_H
#define INC_CLUSTERBOMBCANNON_H

/** \file
 * File for the cluster bomb cannon.
 *
 * @author Nathan Samson
*/

#include "game/weapons/weapon.h"
#include "game/clusterbomb.h"

namespace SI {
	class ClusterBombCannonBlueprint;
	
	/**
	 * A cluster bomb.
	*/
	class ClusterBombCannon: public VWeapon {
	public:
		ClusterBombCannon(const ClusterBombCannonBlueprint&, Ship*);
	
		virtual VGameEntity* fire();
	private:	
		/**
		 * The type of the bomb.
		*/
		ClusterBombType* fBombType;
	};

	/**
	 * A cluster bomb blueprint.
	*/
	class ClusterBombCannonBlueprint: public VWeaponBlueprint {
	public:
		ClusterBombCannonBlueprint(int, IGameEntityFactory*, ClusterBombType*);
	
		virtual ClusterBombCannon* attachWeaponToShip(Ship*);
		
		friend class ClusterBombCannon;
	private:		
		/**
		 * The type of the bomb.
		*/
		ClusterBombType* fBombType;
	};
}

#endif // INC_CLUSTERBOMBCANNON_H
