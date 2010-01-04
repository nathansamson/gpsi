/** \file
 * File for the ship.
 *
 * @author Nathan Samson
*/

#include "game/ship.h"
#include "game/gameentityfactory.h"
#include "misc/boundingbox.h"

namespace SI {

	/**
	 * Default constructor, do not use.
	*/
	ShipType::ShipType(): fBoundingShapeDesc(0) {
	}

	/**
	 * Public constructor.
	 *
	 * @param name The name of the ship.
	 * @param shape The shape of the ship. The shiptype is the owner of this object.
	 * @param weapons A list of weapons
	 * @param speed The speed of the ship
	 * @param hitpoints The hit points
	*/
	ShipType::ShipType(std::string name, IBoundingShapeDescription* shape, 
		         std::vector<std::string> weapons, Vector2 speed, int hitpoints):
		         fBoundingShapeDesc(shape), fName(name), fWeapons(weapons),
		         fMaxSpeed(speed), fHitPoints(hitpoints) {
	}
	
	ShipType::ShipType(const ShipType& other):
	             fName(other.fName), fWeapons(other.fWeapons),
		         fMaxSpeed(other.fMaxSpeed), fHitPoints(other.fHitPoints) {
		if (other.fBoundingShapeDesc) {
			fBoundingShapeDesc = other.fBoundingShapeDesc->copy();
		} else {
			fBoundingShapeDesc = 0;
		}
	}
	
	ShipType& ShipType::operator=(const ShipType& other) {
		if (&other != this) {
			if (fBoundingShapeDesc) {
				delete fBoundingShapeDesc;
			}
			fName = other.fName;
			fWeapons = other.fWeapons;
			fMaxSpeed = other.fMaxSpeed;
			fHitPoints = other.fHitPoints;
			if (other.fBoundingShapeDesc) {
				fBoundingShapeDesc = other.fBoundingShapeDesc->copy();
			} else {
				fBoundingShapeDesc = 0;
			}
		}
		return *this;
	}
	
	/**
	 * Returns the name of the ship.
	 *
	 * @return The name of the ship.
	*/
	std::string ShipType::getName() {
		return fName;
	}
	
	/**
	 * Returns the width of the ship.
	 *
	 * @return The widht of the ship.
	*/
	double ShipType::getWidth() {
		return fBoundingShapeDesc->getWidth();
	}
	
	ShipType::~ShipType() {
		if (fBoundingShapeDesc) delete fBoundingShapeDesc;
	}

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
	 * @param weaponery The weapon depot.
	*/
	Ship::Ship(VShipDriver* driver, Vector2 pos, int dir, EntityGroup* group,
	           ShipType type, IGameEntityFactory* fac, Weaponery* weaponery):
	      VGameEntity(pos, dir, type.fBoundingShapeDesc, group, fac),
	      fShipType(type), fRequestFire(false), fShipDriver(driver),
	      fWeaponery(weaponery), fHP(type.fHitPoints) {
		fShipDriver->bind(this);
		fActiveWeapon = 0;
		for (std::vector<std::string>::iterator it = fShipType.fWeapons.begin(); it != fShipType.fWeapons.end(); it++) {
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
		if (isDead()) {
			return std::vector<VGameEntity*>();
		}
		fShipDriver->update(ticks);
		for(std::vector<VWeapon*>::iterator it = fWeapons.begin(); it != fWeapons.end(); it++) {
			(*it)->update(ticks);
		} 
		std::vector<VGameEntity*> fire;
		
		if (fRequestFire) {
			if (fActiveWeapon < (int)fWeapons.size() && fWeapons[fActiveWeapon] != 0) {
				VGameEntity* p = fWeapons[fActiveWeapon]->fire();
				if (p) {
					fire.push_back(p);
					fGroup->increaseScore(-100);
				}
			}
		}
		fRequestFire = false;
		return fire;
	}
	
	/**
	 * Collide the ship with another entity.
	 *
	 * @param o The other entity.
	*/
	void Ship::collide(VGameEntity* o) {
		if (IProjectile* p = dynamic_cast<IProjectile*>(o)) {
			fHP -= p->getImpact();
			if (fHP <= 0.0) {
				p->getGroup()->increaseScore(500);
				die();
			}
		} else {
			if (dynamic_cast<Ship*>(o) != 0) {
				die();
			}
		}
	}
	
	/**
	 * Returns the health of the ship.
	*/
	double Ship::getHealth() {
		return fHP * 1.0 / fShipType.fHitPoints;
	}
	
	/**
	 * Move the ship.
	 *
	 * @param movement The total movement, it is possible that the resulted movement is not not the same as given, but the ship will try to get at it.
	 * @param ticks The number of ticks
	*/
	void Ship::move(Vector2& movement, int ticks) {
		movement.inBounds(fShipType.fMaxSpeed * ticks, -fShipType.fMaxSpeed * ticks);
		
		if (getPosition().getX() + movement.getX() < -4.0) {
			movement.setX(-4.0 - getPosition().getX());
		}
		
		if (getPosition().getX() + movement.getX() > 4.0) {
			movement.setX(4.0 - getPosition().getX());
		}
		VGameEntity::move(movement);
	}
	
	/**
	 * Instruction for the ShipDriver to fire.
	 * It will only fire when the ship is at able to fire at this moment.
	*/
	void Ship::fire() {
		fRequestFire = true;
	}
}
