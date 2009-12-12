#ifndef INC_GUN_H
#define INC_GUN_H

#include "misc/vector2.h"
#include "game/weapons/weapon.h"
#include "game/bullet.h"

namespace SI {
	class Gun: public VWeapon {
	public:
		Gun(int, IGameEntityFactory*, Ship*, Vector2, BulletType);
		
		virtual VGameEntity* fire();
	private:
		BulletType fBulletType;
		Vector2 fOffset;
	};
}

#endif // INC_GUN_H
