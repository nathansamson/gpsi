#include "game/bullet.h"

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param s The speed of the bullet.
	 * @param pos The position of the bullet.
	 * @param fac The factory of the bullet.
	*/
	Bullet::Bullet(Vector2 s, Vector2 pos, IGameEntityFactory* fac): VGameEntity(pos, fac), fSpeed(s) {
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
