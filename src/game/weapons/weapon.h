#ifndef INC_WEAPON_H
#define INC_WEAPON_H

/** \file
 * File for the weapon.
 *
 * @author Nathan Samson
*/

#include "game/gameentity.h"

namespace SI {
	class Ship;
	class IGameEntityFactory;
	class VWeapon;
	
	/**
	 * Base class for weapon blueprints.
	*/
	class VWeaponBlueprint {
	public:
		VWeaponBlueprint(int, IGameEntityFactory*);
		virtual ~VWeaponBlueprint();
		
		/**
		 * Attach the weapon to a ship.
		 *
		 * @return The complete and attached weapon.
		*/
		virtual VWeapon* attachWeaponToShip(Ship*) = 0;
		
		friend class VWeapon;
	private:
		/**
		 * The entity factory.
		*/
		IGameEntityFactory* fEntityFactory;
	
		/**
		 * The minimal number of ticks between 2 shots.
		*/
		int fTicksBetweenFire;
	};
	
	/**
	 * Base class for all weapons.
	*/
	class VWeapon {
	public:
		virtual ~VWeapon();
	
		/**
		 * Fire off the weapon.
		 *
		 * @return a Projectile (or 0 if the weapon is not able to fire at this moment)
		*/
		virtual VGameEntity* fire() = 0;
		void update(int);
	protected:
		VWeapon(const VWeaponBlueprint&, Ship*);

		void resetTime();
		bool canFire();
		
		/**
		 * The ship.
		*/
		Ship* fShip;
		
		/**
		 * The entity factory.
		*/
		IGameEntityFactory* fEntityFactory;
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
