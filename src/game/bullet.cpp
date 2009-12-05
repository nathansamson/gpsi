#include "game/bullet.h"

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param pos The position of the bullet.
	 * @param type the Bullet information.
	 * @param fac The factory of the bullet.
	*/
	Bullet::Bullet(Vector2 pos, BulletType type, IGameEntityFactory* fac):
	        VGameEntity(pos, type.fBoundingShapeDesc, fac),
	        fSpeed(type.fSpeed) {
	}
	
	/**
	 * Update the state of the bullet.
	 *
	 * @param ticks The number of ticks passed since last update.
	 * @return An empty list of generated entities.
	*/
	std::vector<VGameEntity*> Bullet::update(int ticks) {
		move(fSpeed * ticks);
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
}
