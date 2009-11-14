#ifndef _SDLCONTROLLER_H_
#define _SDLCONTROLLER_H_

#include <SDL/SDL.h>

#include "guiframework/sdlwindow.h"

namespace sdlframework {
	class VSDLController {
		public:
			VSDLController(SDLWindow* window);
			virtual ~VSDLController();
			
			virtual void draw();
			virtual void keyDown(SDL_KeyboardEvent);
			virtual void quit();
		protected:
			SDLWindow* fWindow;
	};
}

#endif
