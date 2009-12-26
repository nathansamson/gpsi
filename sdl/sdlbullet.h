#ifndef INC_SDLBULLET_H
#define INC_SDLBULLET_H

/** \file
 * File for the SDL bullets.
 *
 * @author Nathan Samson
*/

#include "zabbr/sdlwindow.h"
#include "zabbr/resources/imageresource.h"
#include "src/game/bullet.h"

namespace SISDL {
	/**
	 * A SDL Bullet.
	*/
	class SDLBullet: public SI::Bullet {
	public:
		SDLBullet(SI::Vector2, int, SI::EntityGroup*, SI::BulletType*,
		          SI::IGameEntityFactory*, Zabbr::SDLWindow*);
		virtual ~SDLBullet();
	
		virtual std::vector<VGameEntity*> update(int);
		virtual void visualize();
		virtual bool isVisible();
	private:
		void positionToWindowCoords(int&, int&);
		
		/**
		 * The window of the sdlbullet. The sdl bullet draws on this window.
		*/
		Zabbr::SDLWindow* fWindow;
		
		/**
		 * The image resource.
		*/
		Zabbr::ImageResource* fImage;
		
		/**
		 * Number of ticks passed since dead.
		*/
		int ticksSinceDead;
	};
}

#endif // INC_SDLBULLET_H
