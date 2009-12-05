#include "game/ship.h"
#include "game/gameentityfactory.h"
#include "misc/boundingbox.h"

namespace SI {

	/**
	 * Public constructor.
	 *
	 * @param driver The driver for the ship. The ship manages the driver, 
	 *        so the driver will be freed when the ship is descructed.
	 * @param pos The initial position of the ship.
	 * @param type The ship type.
	 * @param fac The factory
	*/
	Ship::Ship(VShipDriver* driver, Vector2 pos, ShipType type, IGameEntityFactory* fac):
	      VGameEntity(pos, type.fBoundingShapeDesc, fac), fRequestFire(false), fShipDriver(driver),
	      fTicksSinceLastFire(minTicksBetweenFire) {
		fShipDriver->bind(this);
	}
	
	/**
	 * Descructor.
	*/
	Ship::~Ship() {
		delete fShipDriver;
	}
	
	/**
	 * Updates the state of the ship.
	 *
	 * @param ticks The number of ticks passed since the last update.
	 * @return A list of generated entities in this update.
	*/
	std::vector<VGameEntity*> Ship::update(int ticks) {
		fShipDriver->update(ticks);
		fTicksSinceLastFire += ticks;
		std::vector<VGameEntity*> fire;
		
		if (hasFired()) {
			fTicksSinceLastFire = 0;
			BulletType bulletType;
			bulletType.fBoundingShapeDesc = new BoundingBoxDescription(0.001, 0.001);
			bulletType.fSpeed = Vector2(0.000, 0.001);
			fire.push_back(fEntityFactory->createBullet(getPosition(), bulletType));
		}
		fRequestFire = false;
		return fire;
	}
	
	/**
	 * Instruction for the ShipDriver to fire.
	 * It will only fire when the ship is at able to fire at this moment.
	*/
	void Ship::fire() {
		fRequestFire = true;
	}
	
	/**
	 * Checks if the ship should fire.
	 *
	 * @return True if the ship has fired.
	*/
	bool Ship::hasFired() {
		return (fRequestFire && fTicksSinceLastFire > minTicksBetweenFire);
	}
}
