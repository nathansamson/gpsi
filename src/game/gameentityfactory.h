#ifndef INC_GAMEENTITYFACTORY_H
#define INC_GAMEENTITYFACTORY_H

#include "game/shipdriver.h"
#include "game/ship.h"
#include "game/bullet.h"

namespace SI {
	struct ShipType;
	class VShipDriver;
	class Ship;

	/**
	 * The Game Entity Factory. Classes that implement this interface
	 * are responsible of creating the specific entity objects that can visualize themselves.
	*/
	class IGameEntityFactory {
	public:
		virtual ~IGameEntityFactory() {}
	
		/**
		 * Creates a Ship.
		*/
		virtual Ship* createShip(VShipDriver*, Vector2, int, EntityGroup*, ShipType) = 0;
		
		/**
		 * Creates a bullet.
		*/
		virtual Bullet* createBullet(Vector2, int, EntityGroup*, BulletType) = 0;
	};
}

#endif // INC_GAMEENTITYFACTORY_H
