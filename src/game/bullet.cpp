#include "game/bullet.h"

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param s The speed of the bullet.
	 * @param pos The position of the bullet.
	*/
	Bullet::Bullet(Vector2 s, Vector2 pos): VGameEntity(pos), fSpeed(s) {
	}
	
	/**
	 * Update the state of the bullet.
	 *
	 * @param ticks The number of ticks passed since last update.
	*/
	void Bullet::update(int ticks) {
		move(fSpeed * ticks);
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
