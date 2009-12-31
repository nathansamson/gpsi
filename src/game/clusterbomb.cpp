/** \file
 * File for the cluserbomb.
 *
 * @author Nathan Samson
*/

#include "game/clusterbomb.h"
#include "game/gameentityfactory.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param shape The shape of the bomb.
	 * @param speed The speed of the bomb
	 * @param ticksAlive The number of ticks before it explodes
	 * @param bulletType The type of the bullet.
	 * @param noBullets The number of bullets.
	*/
	ClusterBombType::ClusterBombType(IBoundingShapeDescription* shape,
	                                 Vector2 speed, int ticksAlive,
	                                 BulletType* bulletType, int noBullets):
	                    AmmoType(shape),
	                    fSpeed(speed), fBulletType(bulletType),
	                    fBullets(noBullets), fMaxTicksAlive(ticksAlive) {
	}
	
	Vector2 ClusterBombType::getSpeed() {
		return fSpeed;
	}
	
	int ClusterBombType::getTicksAlive() {
		return fMaxTicksAlive;
	}
	
	BulletType* ClusterBombType::getBulletType() {
		return fBulletType;
	}
	
	int ClusterBombType::getNumberOfBullets() {
		return fBullets;
	}

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
	    IProjectile(pos, dir, type->getShape(), group, fac),
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
		if (fTicksAlive > fClusterBombType->getTicksAlive()) {
			fExploded = true;
		}
		move(ticks * fClusterBombType->getSpeed());
		if (fExploded) {
			// return something
			std::vector<VGameEntity*> bullets;
			for (int i = 0; i < fClusterBombType->getNumberOfBullets(); i++) {
				int rotated = 0;
				
				rotated = (i+1)*1.0/(fClusterBombType->getNumberOfBullets()+1) * 180 - 90;
				bullets.push_back(fEntityFactory->createBullet(getPosition(), rotated, getGroup(), fClusterBombType->getBulletType()));
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
