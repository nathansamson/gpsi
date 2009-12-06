#ifndef INC_BULLET_H
#define INC_BULLET_H

#include "misc/vector2.h"
#include "game/gameentity.h"

namespace SI {
	/**
	 * Description of a bullet.
	*/
	struct BulletType {
		/**
		 * The speed of the bullet.
		*/
		Vector2 fSpeed;
		
		/**
		 * The bounding shape of the bullet.
		*/
		IBoundingShapeDescription* fBoundingShapeDesc;
	};

	/**
	 * A Bullet class.
	 * The bullet is the simplest type of weapon in the game.
	*/
	class Bullet: public VGameEntity {
	public:
		Bullet(Vector2, int, EntityGroup*, BulletType, IGameEntityFactory*);
		
		virtual std::vector<VGameEntity*> update(int);
		virtual double getImpact();
	private:
		/**
		 * The speed of the bullet. The speed of a bullet is a constant.
		*/
		Vector2 fSpeed;
	};
}

#endif // INC_BULLET_H
