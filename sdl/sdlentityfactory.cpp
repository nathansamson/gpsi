#include "sdlentityfactory.h"
#include "sdlship.h"

namespace SISDL {
	SDLEntityFactory::SDLEntityFactory(Zabbr::SDLWindow* w): fWindow(w) {
	}

	SI::Ship* SDLEntityFactory::createShip(SI::VShipDriver* driver) {
		return new SDLShip(driver, fWindow);
	}
}
