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
	 * @param dir The initial direction of the ship.
	 * @param group The group of the entity
	 * @param type The ship type.
	 * @param fac The factory
	*/
	Ship::Ship(VShipDriver* driver, Vector2 pos, int dir, EntityGroup* group, ShipType type, IGameEntityFactory* fac):
	      VGameEntity(pos, dir, type.fBoundingShapeDesc, group, fac), fRequestFire(false), fShipDriver(driver),
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
			bulletType.fBoundingShapeDesc = new BoundingBoxDescription(0.15, 0.15);
			bulletType.fSpeed = Vector2(0.000, 0.001 * ((getDirection() == 0) ? 1 : -1));
			fire.push_back(fEntityFactory->createBullet(getPosition(), getDirection(), fGroup, bulletType));
			delete bulletType.fBoundingShapeDesc;
		}
		fRequestFire = false;
		return fire;
	}
	
	void Ship::collide(VGameEntity* o) {
		Bullet* b = dynamic_cast<Bullet*>(o);
		if (b != 0) {
			die();
		} else {
			Ship* s = dynamic_cast<Ship*>(o);
			if (s != 0) {
				die();
			}
		}
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
