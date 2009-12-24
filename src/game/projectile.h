#ifndef INC_PROJECTILE_H
#define INC_PROJECTILE_H

#include "game/gameentity.h"

namespace SI {
	class IProjectile: public VGameEntity {
	public:
		IProjectile(Vector2 pos, int dir, IBoundingShapeDescription* bshape,
	                EntityGroup* group, IGameEntityFactory* fac):
	            VGameEntity(pos, dir, bshape, group, fac) {
		}
	
		virtual double getImpact() = 0;
	};
}

#endif // INC_PROJECTILE_H
