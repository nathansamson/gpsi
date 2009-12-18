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
	Ship::Ship(VShipDriver* driver, Vector2 pos, int dir, EntityGroup* group, ShipType type, IGameEntityFactory* fac, Weaponery* weaponery):
	      VGameEntity(pos, dir, type.fBoundingShapeDesc, group, fac), fRequestFire(false), fShipDriver(driver), fWeaponery(weaponery) {
		fShipDriver->bind(this);
		fActiveWeapon = 0;
		for (std::vector<std::string>::iterator it = type.fWeapons.begin(); it != type.fWeapons.end(); it++) {
			fWeapons.push_back(fWeaponery->getWeapon((*it), this));
		}
	}
	
	/**
	 * Descructor.
	*/
	Ship::~Ship() {
		delete fShipDriver;
		for (std::vector<VWeapon*>::iterator it = fWeapons.begin(); it != fWeapons.end(); it++) {
			delete *it;
		}
	}
	
	/**
	 * Updates the state of the ship.
	 *
	 * @param ticks The number of ticks passed since the last update.
	 * @return A list of generated entities in this update.
	*/
	std::vector<VGameEntity*> Ship::update(int ticks) {
		fShipDriver->update(ticks);
		for(std::vector<VWeapon*>::iterator it = fWeapons.begin(); it != fWeapons.end(); it++) {
			(*it)->update(ticks);
		} 
		std::vector<VGameEntity*> fire;
		
		if (fRequestFire) {
			if (fActiveWeapon < (int)fWeapons.size() && fWeapons[fActiveWeapon] != 0) {
				VGameEntity* p = fWeapons[fActiveWeapon]->fire();
				if (p) fire.push_back(p);
			}
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
}
