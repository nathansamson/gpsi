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
	           SI::ClusterBomb(pos, dir, group, t, fac), fWindow(w),
	                      fBoundingBoxDesc(*dynamic_cast<SI::BoundingBoxDescription*>(t->fBoundingShapeDesc)) {
	}
	
	/**
	 * Draws the cluster bomb.
	*/
	void SDLClusterBomb::visualize() {
		int w = fBoundingBoxDesc.getWidth() / 8.0 * fWindow->getXResolution();
		int h = fBoundingBoxDesc.getHeight() / 6.0 * fWindow->getYResolution();
		int x, y;
		positionToWindowCoords(x, y);
		fWindow->drawRectangle(x, y, w, h, 0, 255, 255);
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
