#ifndef INC_GUN_H
#define INC_GUN_H

#include "misc/vector2.h"
#include "game/weapons/weapon.h"
#include "game/bullet.h"

namespace SI {
	class Gun: public VWeapon {
	public:
		Gun(int, IGameEntityFactory*, Vector2, BulletType*);
		
		virtual Gun* addWeaponToShip(Ship*);
		
		virtual VGameEntity* fire();
	private:
		Gun(const Gun&, Ship*);
	
		BulletType* fBulletType;
		Vector2 fOffset;
	};
}

#endif // INC_GUN_H
