#ifndef INC_SHIP_H
#define INC_SHIP_H

/** \file
 * File for the ship.
 *
 * @author Nathan Samson
*/

#include <vector>

#include "misc/vector2.h"
#include "game/shipdriver.h"
#include "game/gameentity.h"
#include "game/weapons/weapon.h"
#include "game/weaponery.h"

namespace SI {

	/**
	 * Description of a ship.
	*/
	class ShipType {
	public:
		ShipType();
		ShipType(std::string, IBoundingShapeDescription*, 
		         std::vector<std::string>, Vector2, int);
		ShipType(const ShipType&);
		ShipType& operator=(const ShipType& other);
		~ShipType();

		std::string getName();
		double getWidth();
		friend class Ship;
	private:
		/**
		 * The bounding shape of the ship.
		*/
		IBoundingShapeDescription* fBoundingShapeDesc;
		
		/**
		 * The name of the ship.
		*/
		std::string fName;
		
		/**
		 * A list of names of weapons of the ship.
		*/
		std::vector<std::string> fWeapons;
		
		/**
		 * The maximum speed of the ship.
		*/
		SI::Vector2 fMaxSpeed;
		
		/**
		 * Total hitpoints of the game.
		*/
		int fHitPoints;
	};

	/**
	 * The Ship class. A Ship represents a space ship in the space.
	*/
	class Ship: public VGameEntity {
	public:
		Ship(VShipDriver*, Vector2, int, EntityGroup*, ShipType, IGameEntityFactory*, Weaponery*);
		virtual ~Ship();
		
		virtual std::vector<VGameEntity*> update(int);
		virtual void collide(VGameEntity*);
		void move(Vector2&, int);
		double getHealth();
		
		friend class VShipDriver;
	protected:
		/**
		 * The type of the ship.
		*/
		ShipType fShipType;
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
	
		/**
		 * The weaponery of the ship.
		*/
		Weaponery* fWeaponery;
		
		/**
		 * The current Health Points of the ship.
		*/
		double fHP;
	};
}

#endif // INC_SHIP_H
