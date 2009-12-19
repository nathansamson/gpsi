#ifndef INC_CLUSTERBOMBCANNON_H
#define INC_CLUSTERBOMBCANNON_H

#include "game/weapons/weapon.h"
#include "game/clusterbomb.h"

namespace SI {
	class ClusterBombCannon: public VWeapon {
	public:
		ClusterBombCannon(int, IGameEntityFactory*, ClusterBombType*);
		
		virtual ClusterBombCannon* addWeaponToShip(Ship*);
		
		virtual VGameEntity* fire();
	private:
		ClusterBombCannon(const ClusterBombCannon&, Ship*);
		
		ClusterBombType* fBombType;
	};
}

#endif // INC_CLUSTERBOMBCANNON_H
