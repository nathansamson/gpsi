#ifndef INC_WEAPON_H
#define INC_WEAPON_H

#include "game/gameentityfactory.h"
#include "game/ship.h"

namespace SI {
	class Ship;
	
	/**
	 * Base class for all weapons.
	*/
	class VWeapon {
	public:
		VWeapon(int, IGameEntityFactory*, Ship*);
		virtual ~VWeapon();
	
		virtual VGameEntity* fire() = 0;
		void update(int);
	protected:
		void resetTime();
		bool canFire();
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
