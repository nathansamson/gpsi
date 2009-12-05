#ifndef INC_SDLBULLET_H
#define INC_SDLBULLET_H

#include "zabbr/sdlwindow.h"
#include "game/bullet.h"

namespace SISDL {
	/**
	 * A SDL Bullet.
	*/
	class SDLBullet: public SI::Bullet {
	public:
		SDLBullet(SI::Vector2, SI::BulletType, SI::IGameEntityFactory*,
		          Zabbr::SDLWindow*);
	
		virtual void visualize();
	private:
		void positionToWindowCoords(int&, int&);
		Zabbr::SDLWindow* fWindow;
	};
}

#endif // INC_SDLBULLET_H
