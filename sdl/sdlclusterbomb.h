#ifndef INC_SDLCLUSTERBOMB_H
#define INC_SDLCLUSTERBOMB_H

/** \file
 * File for the SDL cluster bomb.
 *
 * @author Nathan Samson
*/

#include "zabbr/sdlwindow.h"
#include "zabbr/resources/imageresource.h"

#include "src/game/clusterbomb.h"
#include "src/misc/boundingbox.h"

namespace SISDL {
	/**
	 * A SDL ClusterBomb.
	*/
	class SDLClusterBomb: public SI::ClusterBomb {
	public:
		SDLClusterBomb(SI::Vector2, int, SI::EntityGroup*, SI::ClusterBombType*,
		          SI::IGameEntityFactory*, Zabbr::SDLWindow*);
		virtual ~SDLClusterBomb();
	
		virtual std::vector<VGameEntity*> update(int);
		virtual void visualize();
		virtual bool isVisible();
		
		void onScreenSizeChanged(Zabbr::SDLWindow*, int, int);
	private:
		void positionToWindowCoords(int&, int&);
		
		/**
		 * The window of the sdlcluster bomb. The sdl clusterbomb draws on this window.
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
		 * The callback ID of the screen resized param.
		*/
		int fCbID;
	};
}

#endif // INC_SDLBULLET_H
