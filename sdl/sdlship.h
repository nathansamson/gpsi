#ifndef INC_SDLSHIP_H
#define INC_SDLSHIP_H

#include "src/game/ship.h"
#include "zabbr/resources/imageresource.h"
#include "zabbr/sdlwindow.h"

namespace SISDL {
	/**
	 * A Ship visualized by SDL.
	*/
	class SDLShip: public SI::Ship {
	public:
		SDLShip(SI::VShipDriver*, Zabbr::SDLWindow*);
		virtual ~SDLShip();
		
		virtual void visualize();
	private:
		/**
		 * The image resource.
		*/
		Zabbr::ImageResource* fImage;
		/**
		 * The window.
		*/
		Zabbr::SDLWindow* fWindow;
		
		void positionToWindowCoords(int&, int&);
	};
}

#endif // INC_SDLSHIP_H
