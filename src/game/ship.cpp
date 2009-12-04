#include "game/ship.h"
#include "game/gameentityfactory.h"

namespace SI {

	/**
	 * Public constructor.
	 *
	 * @param driver The driver for the ship. The ship manages the driver, 
	 *        so the driver will be freed when the ship is descructed.
	 * @param v The initial position of the ship.
	 * @param fac The factory
	*/
	Ship::Ship(VShipDriver* driver, Vector2 v, IGameEntityFactory* fac): VGameEntity(v, fac), fRequestFire(false), fShipDriver(driver), fTicksSinceLastFire(minTicksBetweenFire) {
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
		
		if (hasFired()) {
			fRequestFire = false;
			fTicksSinceLastFire = 0;
			std::vector<VGameEntity*> fire;
			fire.push_back(fEntityFactory->createBullet(Vector2(0.000, 0.001), getPosition()));
			return fire;
		}
		return std::vector<VGameEntity*>();
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
