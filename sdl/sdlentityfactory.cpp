#include "sdlentityfactory.h"
#include "sdlship.h"
#include "sdlbullet.h"

namespace SISDL {
	/**
	 * Public constructor
	 *
	 * @param w The window
	*/
	SDLEntityFactory::SDLEntityFactory(Zabbr::SDLWindow* w): fWindow(w) {
	}

	/**
	 * Creates a ship.
	 *
	 * @param driver The driver for the ship.
	 * @param d The initial direction of the ship.
	 * @param g The group of the entity.
	 * @param v The initial position.
	 * @param t The type of the ship.
	*/
	SI::Ship* SDLEntityFactory::createShip(SI::VShipDriver* driver, SI::Vector2 v, int d, SI::EntityGroup* g, SI::Weaponery* w, SI::ShipType t) {
		return new SDLShip(driver, v, d, g, t, this, w, fWindow);
	}
	
	/**
	 * Creates a bullet
	 *
	 * @param pos The initial position of the bullet.
	 * @param dir The initial direction of the bullet.
	 * @param t Bullet information
	*/
	SI::Bullet* SDLEntityFactory::createBullet(SI::Vector2 pos, int dir, SI::EntityGroup* g, SI::BulletType t) {
		return new SDLBullet(pos, dir, g, t, this, fWindow);
	}
}
