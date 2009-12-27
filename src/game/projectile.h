#ifndef INC_PROJECTILE_H
#define INC_PROJECTILE_H

/** \file
 * File for the projectile.
 *
 * @author Nathan Samson
*/

#include "game/gameentity.h"

namespace SI {
	/**
	 * Base class for projectiles.
	*/
	class IProjectile: public VGameEntity {
	public:
		/**
		 * Public constructor.
		 *
		 * @param pos The initial position.
		 * @param dir The direction of the projectile.
		 * @param bshape The bounding shape of the projectile.
		 * @param group The group of the entity.
		 * @param fac Entity factory.
		*/
		IProjectile(Vector2 pos, int dir, IBoundingShapeDescription* bshape,
	                EntityGroup* group, IGameEntityFactory* fac):
	            VGameEntity(pos, dir, bshape, group, fac) {
		}
	
		/**
		 * Returns the impact of the projectile.
		 *
		 * @return the impact of the projectile.
		*/
		virtual double getImpact() = 0;
	};
}

#endif // INC_PROJECTILE_H
