#ifndef INC_SDLCLUSTERBOMB_H
#define INC_SDLCLUSTERBOMB_H

#include "zabbr/sdlwindow.h"
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
	
		virtual void visualize();
	private:
		void positionToWindowCoords(int&, int&);
		
		/**
		 * The window of the sdlcluster bomb. The sdl clusterbomb draws on this window.
		*/
		Zabbr::SDLWindow* fWindow;
		
		/**
		 * The bounding box of the bomb.
		*/
		SI::BoundingBoxDescription fBoundingBoxDesc;
	};
}

#endif // INC_SDLBULLET_H
