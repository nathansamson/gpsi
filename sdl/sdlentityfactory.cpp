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
	*/
	SI::Ship* SDLEntityFactory::createShip(SI::VShipDriver* driver, SI::Vector2 v) {
		return new SDLShip(driver, v, this, fWindow);
	}
	
	/**
	 * Creates a bullet
	 *
	 * @param speed The speed of the bullet
	 * @param pos The initial position of the bullet.
	*/
	SI::Bullet* SDLEntityFactory::createBullet(SI::Vector2 speed, SI::Vector2 pos) {
		return new SDLBullet(speed, pos, this, fWindow);
	}
}
