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
	 * @param v The initial position.
	 * @param t The type of the ship.
	*/
	SI::Ship* SDLEntityFactory::createShip(SI::VShipDriver* driver, SI::Vector2 v, int d, SI::ShipType t) {
		return new SDLShip(driver, v, d, t, this, fWindow);
	}
	
	/**
	 * Creates a bullet
	 *
	 * @param pos The initial position of the bullet.
	 * @param dir The initial direction of the bullet.
	 * @param t Bullet information
	*/
	SI::Bullet* SDLEntityFactory::createBullet(SI::Vector2 pos, int dir, SI::BulletType t) {
		return new SDLBullet(pos, dir, t, this, fWindow);
	}
}
