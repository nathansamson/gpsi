#ifndef INC_GAMEENTITYFACTORY_H
#define INC_GAMEENTITYFACTORY_H

#include "game/shipdriver.h"
#include "game/ship.h"
#include "game/bullet.h"
#include "game/clusterbomb.h"
#include "game/weaponery.h"

namespace SI {

	/**
	 * The Game Entity Factory. Classes that implement this interface
	 * are responsible of creating the specific entity objects that can visualize themselves.
	*/
	class IGameEntityFactory {
	public:
		virtual ~IGameEntityFactory() {}
	
		/**
		 * Creates a user Ship.
		*/
		virtual Ship* createUserShip(VShipDriver*, Vector2, int, EntityGroup*, Weaponery*, ShipType) = 0;
	
		/**
		 * Creates an AI Ship.
		*/
		virtual Ship* createAIShip(VShipDriver*, Vector2, int, EntityGroup*, Weaponery*, ShipType) = 0;
		
		/**
		 * Creates a bullet.
		*/
		virtual Bullet* createBullet(Vector2, int, EntityGroup*, BulletType*) = 0;
		
		/**
		 * Creates a cluster bomb.
		*/
		virtual ClusterBomb* createClusterBomb(Vector2, int, EntityGroup*, ClusterBombType*) = 0;
	};
}

#endif // INC_GAMEENTITYFACTORY_H
