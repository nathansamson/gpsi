#ifndef INC_GUN_H
#define INC_GUN_H

#include "misc/vector2.h"
#include "game/weapons/weapon.h"
#include "game/bullet.h"

namespace SI {
	class GunBlueprint;
	
	/**
	 * A Gun weapon.
	*/
	class Gun: public VWeapon {
	public:
		Gun(const GunBlueprint&, Ship*);
		virtual  ~Gun();
		
		virtual VGameEntity* fire();
	private:
		/**
		 * The type of the bullet.
		*/
		BulletType* fBulletType;
		
		/**
		 * The offset to the ship.
		*/
		Vector2 fOffset;
	};

	/**
	 * A Gun blueprint weapon.
	*/
	class GunBlueprint: public VWeaponBlueprint {
	public:
		GunBlueprint(int, IGameEntityFactory*, Vector2, BulletType*);
		virtual  ~GunBlueprint();
		
		virtual Gun* attachWeaponToShip(Ship*);
		
		friend class Gun;
	private:
		/**
		 * The type of the bullet.
		*/
		BulletType* fBulletType;
		
		/**
		 * The offset to the ship.
		*/
		Vector2 fOffset;
	};
}

#endif // INC_GUN_H
