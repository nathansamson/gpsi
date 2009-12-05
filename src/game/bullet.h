#ifndef INC_BULLET_H
#define INC_BULLET_H

#include "misc/vector2.h"
#include "game/gameentity.h"

namespace SI {
	struct BulletType {
		Vector2 fSpeed;
		IBoundingShapeDescription* fBoundingShapeDesc;
	};

	/**
	 * A Bullet class.
	 * The bullet is the simplest type of weapon in the game.
	*/
	class Bullet: public VGameEntity {
	public:
		Bullet(Vector2, BulletType, IGameEntityFactory*);
		
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
