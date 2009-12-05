#include "sdlship.h"

#include "zabbr/resources/resourcemanager.h"
#include "src/misc/vector2.h"
#include "src/misc/boundingbox.h"

namespace SISDL {
	/**
	 * Public constructor.
	 *
	 * @param driver The driver for the ship.
	 * @param w The window
	*/
	SDLShip::SDLShip(SI::VShipDriver* driver, SI::Vector2 v,
	                 SI::ShipType t, SI::IGameEntityFactory* fac,
	                 Zabbr::SDLWindow* w):
	         SI::Ship(driver, v, t, fac), fWindow(w) {
	    SI::BoundingBoxDescription* bb = dynamic_cast<SI::BoundingBoxDescription*>(t.fBoundingShapeDesc);
	    int width = bb->getWidth() / 8.0 * fWindow->getXResolution();
	    int height = bb->getHeight() / 6.0 * fWindow->getYResolution();
		fImage = Zabbr::ResourceManager::manager().image(t.fName+".png", width, height, true);
	}
	
	/**
	 * Destructor.
	*/
	SDLShip::~SDLShip() {
		 Zabbr::ResourceManager::manager().free(fImage);
	}
	
	/**
	 * Draws the ship.
	*/
	void SDLShip::visualize() {
		int x, y;
		positionToWindowCoords(x, y);
		fWindow->drawSurface(fImage, x, y);
	}
	
	/**
	 * Convert world coordinates to screen coordinates.
	 * It also accounts for offset of the image size.
	 *
	 * @param x The x screen-coordinate
	 * @param y The y screen-coordinate
	*/
	void SDLShip::positionToWindowCoords(int& x, int& y) {
		SI::Vector2 p ((getPosition() + SI::Vector2(4.0, -3.0)) * (fWindow->getXResolution()/8));
		p -= SI::Vector2(fImage->getWidth() / 2, - fImage->getHeight() / 2);
		
		x = p.getX();
		y = -p.getY();
	}

}
