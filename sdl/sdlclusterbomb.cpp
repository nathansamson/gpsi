#include "zabbr/resources/resourcemanager.h"
#include "sdl/sdlclusterbomb.h"
#include "src/misc/boundingbox.h"


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
	           SI::ClusterBomb(pos, dir, group, t, fac), fWindow(w), ticksSinceDead(0) {
		SI::BoundingBoxDescription* bb = dynamic_cast<SI::BoundingBoxDescription*>(t->fBoundingShapeDesc);
	    int width = bb->getWidth() / 8.0 * fWindow->getXResolution();
	    int height = bb->getHeight() / 6.0 * fWindow->getYResolution();
		fImage = Zabbr::ResourceManager::manager().image("clusterbomb.png", width, height, true, dir);
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
		SI::Vector2 p ((getPosition() + SI::Vector2(4.0, -3.0)) * (fWindow->getXResolution()/8));
		p -= SI::Vector2(5, - 5);
		
		x = p.getX();
		y = -p.getY();
	}
}
