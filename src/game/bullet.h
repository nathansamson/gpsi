#ifndef INC_BULLET_H
#define INC_BULLET_H

/** \file
 * File for the bullet.
 *
 * @author Nathan Samson
*/

#include "misc/vector2.h"
#include "game/ammotype.h"
#include "game/projectile.h"

namespace SI {
	/**
	 * Description of a bullet.
	*/
	class BulletType: public AmmoType {
	public:
		BulletType(IBoundingShapeDescription*, Vector2);
	
		Vector2 getSpeed();
	private:
		/**
		 * The speed of the bullet.
		*/
		Vector2 fSpeed;
	};

	/**
	 * A Bullet class.
	 * The bullet is the simplest type of weapon in the game.
	*/
	class Bullet: public IProjectile {
	public:
		Bullet(Vector2, int, EntityGroup*, BulletType*, IGameEntityFactory*);
		
		virtual std::vector<VGameEntity*> update(int);
		virtual double getImpact();
		virtual void collide(VGameEntity*);
	private:
		/**
		 * The speed of the bullet. The speed of a bullet is a constant.
		*/
		Vector2 fSpeed;
	};
}

#endif // INC_BULLET_H
