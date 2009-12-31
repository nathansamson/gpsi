/** \file
 * File for the sdl ship.
 *
 * @author Nathan Samson
*/
#include "sdlship.h"

#include "zabbr/resources/resourcemanager.h"
#include "zabbr/events/callbacks.h"
#include "src/misc/vector2.h"

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
	    int width = getWidth() / 8.0 * fWindow->getXResolution();
	    int height = getHeight() / 6.0 * fWindow->getYResolution();
		fImage = Zabbr::ResourceManager::manager().image(t.getName()+".png", width, height, false, dir);
		fCbID = fWindow->connectOnScreenSizeChanged(new Zabbr::ClassCallback3<SDLShip, Zabbr::SDLWindow*, int, int>(this, &SDLShip::onScreenSizeChanged));
	}
	
	/**
	 * Destructor.
	*/
	SDLShip::~SDLShip() {
		 Zabbr::ResourceManager::manager().free(fImage);
		 fWindow->disconnectOnScreenSizeChanged(fCbID);
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
		double tX = getPosition().getX();
		double tY = getPosition().getY();
		tX += 4;
		tY = 3 - tY;
		tX *= fWindow->getXResolution() / 8.0;
		tY *= fWindow->getYResolution() / 6.0;
		
		tX -= fImage->getWidth() / 2;
		tY -= fImage->getHeight() / 2;
		x = tX;
		y = tY;
	}

	/**
	 * The on screen size changed event.
	 *
	 * @param w The window that fired the event.
	 * @param x The x resolution.
	 * @param y The y resolution. 
	*/
	void SDLShip::onScreenSizeChanged(Zabbr::SDLWindow* w, int x, int y) {
		Zabbr::ResourceManager::manager().free(fImage);
		int width = getWidth() / 8.0 * x;
	    int height = getHeight() / 6.0 * y;
		fImage = Zabbr::ResourceManager::manager().image(fShipType.getName()+".png", width, height, false, getDirection());
	}
}
