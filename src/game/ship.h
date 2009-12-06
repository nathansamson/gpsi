#ifndef INC_SHIP_H
#define INC_SHIP_H

#include "misc/vector2.h"
#include "game/shipdriver.h"
#include "game/gameentity.h"

namespace SI {
	class VShipDriver;

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
		friend class VShipDriver;
	protected:
		bool hasFired();
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
		 * The number of ticks passed since last fire.
		*/
		int fTicksSinceLastFire;
		
		static const int minTicksBetweenFire = 10000;
	};
}

#endif // INC_SHIP_H
