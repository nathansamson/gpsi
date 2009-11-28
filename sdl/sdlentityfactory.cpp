#include "sdlentityfactory.h"
#include "sdlship.h"

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
	SI::Ship* SDLEntityFactory::createShip(SI::VShipDriver* driver) {
		return new SDLShip(driver, fWindow);
	}
}
