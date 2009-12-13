#ifndef INC_SHIP_H
#define INC_SHIP_H

#include <vector>

#include "misc/vector2.h"
#include "game/shipdriver.h"
#include "game/gameentity.h"
#include "game/weapons/weapon.h"
#include "game/bullet.h"

namespace SI {
	class VShipDriver;
	class VWeapon;

	/**
	 * Description of a ship.
	*/
	struct ShipType {
		/**
		 * The bounding shape of the ship.
		*/
		IBoundingShapeDescription* fBoundingShapeDesc;
		
		/**
		 * The name of the ship.
		*/
		std::string fName;
	};

	/**
	 * The Ship class. A Ship represents a space ship in the space.
	*/
	class Ship: public VGameEntity {
	public:
		Ship(VShipDriver*, Vector2, int, EntityGroup*, ShipType, IGameEntityFactory*);
		virtual ~Ship();
		
		virtual std::vector<VGameEntity*> update(int);
		virtual void collide(VGameEntity*);
		
		friend class VShipDriver;
	private:
		void fire();
		
		/**
		 * Request to fire.
		*/
		bool fRequestFire;
	
		/**
		 * The ship driver.
		*/
		VShipDriver* fShipDriver;
		
		/**
		 * The index of the current active weapon. (the index of the vector fWeapons)
		*/
		int fActiveWeapon;
		
		/**
		 * The list of weapons on this ship.
		*/
		std::vector<VWeapon*> fWeapons;
		
		BulletType fBulletType;
	};
}

#endif // INC_SHIP_H
