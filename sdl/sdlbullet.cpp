#include "zabbr/resources/resourcemanager.h"
#include "src/misc/boundingbox.h"

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
		SI::BoundingBoxDescription* bb = dynamic_cast<SI::BoundingBoxDescription*>(t->fBoundingShapeDesc);
	    int width = bb->getWidth() / 8.0 * fWindow->getXResolution();
	    int height = bb->getHeight() / 6.0 * fWindow->getYResolution();
		fImage = Zabbr::ResourceManager::manager().image("bullet.png", width, height, true, dir);
	}
	
	SDLBullet::~SDLBullet() {
		Zabbr::ResourceManager::manager().free(fImage);
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
		SI::Vector2 p ((getPosition() + SI::Vector2(4.0, -3.0)) * (fWindow->getXResolution()/8));
		p -= SI::Vector2(5, - 5);
		
		x = p.getX();
		y = -p.getY();
	}
}
