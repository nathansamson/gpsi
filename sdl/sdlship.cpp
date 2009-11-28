#include "sdlship.h"

#include "zabbr/resources/resourcemanager.h"
#include "src/misc/vector2.h"

namespace SISDL {
	SDLShip::SDLShip(SI::VShipDriver* driver, Zabbr::SDLWindow* w): SI::Ship(driver), fWindow(w) {
		fImage = Zabbr::ResourceManager::manager().image("stallaris_spaceship.png");
	}
	
	SDLShip::~SDLShip() {
		 Zabbr::ResourceManager::manager().free(fImage);
	}
	
	void SDLShip::visualize() {
		int x, y;
		positionToWindowCoords(x, y);
		fWindow->drawSurface(fImage, x, y);
	}
	
	void SDLShip::positionToWindowCoords(int& x, int& y) {
		SI::Vector2 p ((getPosition() + SI::Vector2(4.0, 3.0)) * 50);
		p -= SI::Vector2(fImage->getWidth() / 2, fImage->getHeight() / 2);
		
		x = p.getX();
		y = p.getY();
	}
}
