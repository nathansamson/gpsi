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
#include "src/misc/boundingbox.h"

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
		
		void onScreenSizeChanged(Zabbr::SDLWindow*, int, int);
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
		
		/**
		 * The bounding box of the bullet.
		*/
		SI::BoundingBoxDescription fBoundingBox;
		
		/**
		 * The callback ID of the screen resized param.
		*/
		int fCbID;
	};
}

#endif // INC_SDLBULLET_H
