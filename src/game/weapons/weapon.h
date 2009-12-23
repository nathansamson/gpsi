#ifndef INC_WEAPON_H
#define INC_WEAPON_H

#include "game/gameentity.h"

namespace SI {
	class Ship;
	class IGameEntityFactory;
	
	/**
	 * Base class for all weapons.
	*/
	class VWeapon {
	public:
		virtual ~VWeapon();
	
	
		/**
		 * Attach the weapon to a ship.
		 *
		 * @return The complete and attached weapon.
		*/
		virtual VWeapon* addWeaponToShip(Ship*) = 0;
	
		/**
		 * Fire off the weapon.
		 *
		 * @return a Projectile (or 0 if the weapon is not able to fire at this moment)
		*/
		virtual VGameEntity* fire() = 0;
		void update(int);
	protected:
		VWeapon(int, IGameEntityFactory*);
		VWeapon(const VWeapon&, Ship*);
		
		bool isBlueprint();
		void resetTime();
		bool canFire();
		
		/**
		 * The entity factory.
		*/
		IGameEntityFactory* fEntityFactory;
		
		/**
		 * The ship.
		*/
		Ship* fShip;
	private:
		/**
		 * The minimal number of ticks between 2 shots.
		*/
		int fTicksBetweenFire;
		
		/**
		 * The number of ticks since last shot.
		*/
		int fTicksSinceLastFire;
	};
}

#endif // INC_WEAPON_H
