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
	                     SI::BulletType t, SI::IGameEntityFactory* fac,
	                     Zabbr::SDLWindow* w):
	           SI::Bullet(speed, dir, group, t, fac), fWindow(w), fBoundingBoxDesc(*dynamic_cast<SI::BoundingBoxDescription*>(t.fBoundingShapeDesc)) {
//		fBoundingBoxDesc = *dynamic_cast<SI::BoundingBoxDescription*>(t.fBoundingShapeDesc);
	}
	
	/**
	 * Draws the bullet.
	*/
	void SDLBullet::visualize() {
		int w = fBoundingBoxDesc.getWidth() / 8.0 * fWindow->getXResolution();
		int h = fBoundingBoxDesc.getHeight() / 6.0 * fWindow->getYResolution();
		int x, y;
		positionToWindowCoords(x, y);
		fWindow->drawRectangle(x, y, w, h, 0, 0, 255);
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
