#ifndef INC_SDLBULLET_H
#define INC_SDLBULLET_H

#include "zabbr/sdlwindow.h"
#include "src/game/bullet.h"
#include "src/misc/boundingbox.h"

namespace SISDL {
	/**
	 * A SDL Bullet.
	*/
	class SDLBullet: public SI::Bullet {
	public:
		SDLBullet(SI::Vector2, int, SI::EntityGroup*, SI::BulletType,
		          SI::IGameEntityFactory*, Zabbr::SDLWindow*);
	
		virtual void visualize();
	private:
		void positionToWindowCoords(int&, int&);
		
		/**
		 * The window of the sdlbullet. The sdl bullet draws on this window.
		*/
		Zabbr::SDLWindow* fWindow;
		
		SI::BoundingBoxDescription fBoundingBoxDesc;
	};
}

#endif // INC_SDLBULLET_H
