/** \file
 * File for the SDL bullet.
 *
 * @author Nathan Samson
*/

#include "zabbr/resources/resourcemanager.h"

#include "sdlbullet.h"

namespace SISDL {
	/**
	 * Constructor.
	 *
	 * @param speed The speed of the bullet.
	 * @param dir The direction of the bullet.
	 * @param group The group of the bullet.
	 * @param t The bullet type.
	 * @param fac The factory.
	 * @param w The window.
	*/
	SDLBullet::SDLBullet(SI::Vector2 speed, int dir, SI::EntityGroup* group,
	                     SI::BulletType* t, SI::IGameEntityFactory* fac,
	                     Zabbr::SDLWindow* w):
	           SI::Bullet(speed, dir, group, t, fac), fWindow(w), ticksSinceDead(0) {
	    int width = getWidth() / 8.0 * fWindow->getXResolution();
	    int height = getHeight() / 6.0 * fWindow->getYResolution();
		fImage = Zabbr::ResourceManager::manager().image("bullet.png", width, height, false, dir);
		fCbID = fWindow->connectOnScreenSizeChanged(new Zabbr::ClassCallback3<SDLBullet, Zabbr::SDLWindow*, int, int>(this, &SDLBullet::onScreenSizeChanged));
	}
	
	SDLBullet::~SDLBullet() {
		Zabbr::ResourceManager::manager().free(fImage);
		fWindow->disconnectOnScreenSizeChanged(fCbID);
	}
	
	/**
	 * Draws the bullet.
	*/
	void SDLBullet::visualize() {
		int x, y;
		positionToWindowCoords(x, y);
		fWindow->drawSurface(fImage, x, y);
		
		if (isDead()) {
			fWindow->drawRectangle(x, y, fImage->getWidth(), fImage->getHeight(), 0, 0, 0, 1.0 / (100.0 / ticksSinceDead));
		}
	}
	
	/**
	 * Updates the SDL entity.
	 *
	 * @param ticks The ticks passed since last update.
	 *
	 * @return a list of new entities.
	*/
	std::vector<SI::VGameEntity*> SDLBullet::update(int ticks) {
		if (isDead()) {
			ticksSinceDead += ticks;
		}
		return Bullet::update(ticks);
	}
	
	/**
	 * Checks if the SDL entity is still visible.
	 *
	 * @return True if the entity is still visible, false if not.
	*/
	bool SDLBullet::isVisible() {
		return ticksSinceDead < 100;
	}
	
	/**
	 * Convert world coordinates to screen coordinates.
	 * It also accounts for offset of the image size.
	 *
	 * @param x The x screen-coordinate
	 * @param y The y screen-coordinate
	*/
	void SDLBullet::positionToWindowCoords(int& x, int& y) {
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
	void SDLBullet::onScreenSizeChanged(Zabbr::SDLWindow* w, int x, int y) {
		Zabbr::ResourceManager::manager().free(fImage);
		int width = getWidth() / 8.0 * x;
	    int height = getHeight() / 6.0 * y;
		fImage = Zabbr::ResourceManager::manager().image("bullet.png", width, height, false, getDirection());
	}
}
