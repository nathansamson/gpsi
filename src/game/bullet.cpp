/** \file
 * File for the bullet.
 *
 * @author Nathan Samson
*/

#include "game/bullet.h"

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param pos The position of the bullet.
	 * @param dir The direction of the bullet.
 	 * @param group The group of the bullet.
	 * @param type the Bullet information.
	 * @param fac The factory of the bullet.
	*/
	Bullet::Bullet(Vector2 pos, int dir, EntityGroup* group, BulletType* type, IGameEntityFactory* fac):
	        IProjectile(pos, dir, type->fBoundingShapeDesc, group, fac),
	        fSpeed(type->fSpeed.rotate(dir)) {
	}
	
	/**
	 * Update the state of the bullet.
	 *
	 * @param ticks The number of ticks passed since last update.
	 * @return An empty list of generated entities.
	*/
	std::vector<VGameEntity*> Bullet::update(int ticks) {
		if (isDead()) {
			return std::vector<VGameEntity*>();
		}
		move(fSpeed * ticks);
		if (getPosition().getY() > 3.0 || getPosition().getY() < -3.0) {
			die();
		}
		return std::vector<VGameEntity*>();
	}
	
	/**
	 * Get the impact of the weapon when it hits anoter entity.
	 *
	 * @return The impact of the bullet.
	*/
	double Bullet::getImpact() {
		return 1.0;
	}
	
	/**
	 * Collide the bullet with another entity.
	 *
	 * @param o The other entity.
	*/
	void Bullet::collide(VGameEntity* o) {
		die();
	}
}
