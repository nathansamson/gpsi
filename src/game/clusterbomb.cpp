#include "game/clusterbomb.h"
#include "game/gameentityfactory.h"

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param pos The position of the cluster bomb.
	 * @param dir The direction of the bomb.
	 * @param group The group of the cluster bomb.
	 * @param type The type of the cluster bomb.
	 * @param fac The entity factory of the bomb.
	*/
	ClusterBomb::ClusterBomb(Vector2 pos, int dir, EntityGroup* group,
	                         ClusterBombType* type, IGameEntityFactory* fac):
	    IProjectile(pos, dir, type->fBoundingShapeDesc, group, fac),
	    fClusterBombType(type), fTicksAlive(0), fExploded(false) {
	}
	
	/**
	 * Update the clusterbomb. It will move itself, or explode.
	 *
	 * @param ticks The number of ticks passed since last update.
	 *
	 * @return A list of other bombs.
	*/
	std::vector<VGameEntity*> ClusterBomb::update(int ticks) {
		if (isDead()) {
			return std::vector<VGameEntity*>();
		}
		fTicksAlive += ticks;
		if (fTicksAlive > fClusterBombType->fMaxTicksAlive) {
			fExploded = true;
		}
		move(ticks * fClusterBombType->fSpeed);
		if (fExploded) {
			// return something
			std::vector<VGameEntity*> bullets;
			for (int i = 0; i < fClusterBombType->fBullets; i++) {
				int rotated = 0;
				
				rotated = (i+1)*1.0/(fClusterBombType->fBullets+1) * 180 - 90;
				bullets.push_back(fEntityFactory->createBullet(getPosition(), rotated, getGroup(), fClusterBombType->fBulletType));
			}
			die();
			return bullets;
		} else {
			return std::vector<VGameEntity*>();
		}
	}
	
	/**
	 * Get the impact of the projectile.
	 *
	 * @return the impact.
	*/
	double ClusterBomb::getImpact() {
		return 0.0;
	}

	/**
	 * Collide with another entity. The bomb will explode.
	 *
	 * @param other The other entity.
	*/	
	void ClusterBomb::collide(VGameEntity* other) {
		fExploded = true;
	}
}
