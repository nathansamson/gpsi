/** \file
 * File for the sdl ship.
 *
 * @author Nathan Samson
*/

#include "sdlship.h"

#include "zabbr/resources/resourcemanager.h"
#include "src/misc/vector2.h"
#include "src/misc/boundingbox.h"

namespace SISDL {
	/**
	 * Public constructor.
	 *
	 * @param driver The driver for the ship.
	 * @param v The initial position.
	 * @param dir The direction of the ship
	 * @param group The group of the entity.
	 * @param t The ship type.
	 * @param fac The Factory.
	 * @param weaponery The weaponery of the ship.
 	 * @param w The window.
	*/
	SDLShip::SDLShip(SI::VShipDriver* driver, SI::Vector2 v, int dir,
	                 SI::EntityGroup* group,
	                 SI::ShipType t, SI::IGameEntityFactory* fac,
	                 SI::Weaponery* weaponery, Zabbr::SDLWindow* w):
	         SI::Ship(driver, v, dir, group, t, fac, weaponery), fWindow(w), ticksSinceDead(0) {
	    SI::BoundingBoxDescription* bb = dynamic_cast<SI::BoundingBoxDescription*>(t.fBoundingShapeDesc);
	    int width = bb->getWidth() / 8.0 * fWindow->getXResolution();
	    int height = bb->getHeight() / 6.0 * fWindow->getYResolution();
		fImage = Zabbr::ResourceManager::manager().image(t.fName+".png", width, height, true, dir);
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
		
		if (isDead()) {
			fWindow->drawRectangle(x, y, fImage->getWidth(), fImage->getHeight(), 0, 0, 0, 1.0 / (1000.0 / ticksSinceDead));
		}
	}
	
	/**
	 * Updates the SDL entity.
	 *
	 * @param ticks The ticks passed since last update.
	 *
	 * @return a list of new entities.
	*/
	std::vector<SI::VGameEntity*> SDLShip::update(int ticks) {
		if (isDead()) {
			ticksSinceDead += ticks;
		}
		return Ship::update(ticks);
	}
	
	/**
	 * Checks if the SDL entity is still visible.
	 *
	 * @return True if the entity is still visible, false if not.
	*/
	bool SDLShip::isVisible() {
		return ticksSinceDead < 1000;
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
