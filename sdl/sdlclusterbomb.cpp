/** \file
 * File for the SDL cluster bomb.
 *
 * @author Nathan Samson
*/

#include "zabbr/resources/resourcemanager.h"
#include "sdl/sdlclusterbomb.h"

namespace SISDL {
	/**
	 * Constructor.
	 *
	 * @param pos The pos of the clusterbomb.
	 * @param dir The direction of the clusterbomb.
	 * @param group The group of the clusterbomb.
	 * @param t The clusterbomb type.
	 * @param fac The factory.
	 * @param w The window.
	*/
	SDLClusterBomb::SDLClusterBomb(SI::Vector2 pos, int dir, SI::EntityGroup* group,
	                     SI::ClusterBombType* t, SI::IGameEntityFactory* fac,
	                     Zabbr::SDLWindow* w):
	           SI::ClusterBomb(pos, dir, group, t, fac), fWindow(w), ticksSinceDead(0),
	           fBoundingBox(SI::BoundingBoxDescription(*dynamic_cast<SI::BoundingBoxDescription*>(t->fBoundingShapeDesc))) {
		int width = fBoundingBox.getWidth() / 8.0 * fWindow->getXResolution();
	    int height = fBoundingBox.getHeight() / 6.0 * fWindow->getYResolution();
		fImage = Zabbr::ResourceManager::manager().image("clusterbomb.png", width, height, false, dir);
		fCbID = fWindow->connectOnScreenSizeChanged(new Zabbr::ClassCallback3<SDLClusterBomb, Zabbr::SDLWindow*, int, int>(this, &SDLClusterBomb::onScreenSizeChanged));
	}
	
	SDLClusterBomb::~SDLClusterBomb() {
		Zabbr::ResourceManager::manager().free(fImage);
		fWindow->disconnectOnScreenSizeChanged(fCbID);
	}
	
	/**
	 * Draws the cluster bomb.
	*/
	void SDLClusterBomb::visualize() {
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
	std::vector<SI::VGameEntity*> SDLClusterBomb::update(int ticks) {
		if (isDead()) {
			ticksSinceDead += ticks;
		}
		return ClusterBomb::update(ticks);
	}
	
	/**
	 * Checks if the SDL entity is still visible.
	 *
	 * @return True if the entity is still visible, false if not.
	*/
	bool SDLClusterBomb::isVisible() {
		return ticksSinceDead < 100;
	}
	
	/**
	 * Convert world coordinates to screen coordinates.
	 * It also accounts for offset of the image size.
	 *
	 * @param x The x screen-coordinate
	 * @param y The y screen-coordinate
	*/
	void SDLClusterBomb::positionToWindowCoords(int& x, int& y) {
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
	void SDLClusterBomb::onScreenSizeChanged(Zabbr::SDLWindow* w, int x, int y) {
		Zabbr::ResourceManager::manager().free(fImage);
		int width = fBoundingBox.getWidth() / 8.0 * x;
	    int height = fBoundingBox.getHeight() / 6.0 * y;
		fImage = Zabbr::ResourceManager::manager().image("bullet.png", width, height, false, getDirection());
	}
}
