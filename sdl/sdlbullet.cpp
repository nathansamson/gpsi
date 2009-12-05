#include "sdlbullet.h"

namespace SISDL {
	/**
	 * Constructor.
	 *
	 * @param speed The speed of the bullet.
	 * @param t The bullet type.
	 * @param fac The factory.
	 * @param w The window.
	*/
	SDLBullet::SDLBullet(SI::Vector2 speed, SI::BulletType t,
	                     SI::IGameEntityFactory* fac,
	                     Zabbr::SDLWindow* w):
	           SI::Bullet(speed, t, fac), fWindow(w) {
	}
	
	/**
	 * Draws the bullet.
	*/
	void SDLBullet::visualize() {
		int x, y;
		positionToWindowCoords(x, y);
		fWindow->drawRectangle(x, y, 10, 10, 0, 0, 255);
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
