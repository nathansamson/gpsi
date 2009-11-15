#ifndef _SDLCONTROLLER_H_
#define _SDLCONTROLLER_H_

#include "SDL.h"

#include "guiframework/sdlwindow.h"

namespace sdlframework {
	class VSDLController {
		public:
			VSDLController(SDLWindow* window);
			virtual ~VSDLController();
			
			virtual void draw();
			virtual void keyDown(SDL_KeyboardEvent);
			virtual void mouseMotion(SDL_MouseMotionEvent);
			virtual void mouseButton(SDL_MouseButtonEvent);
			virtual void quit();
			void openParentController();
			void openController(VSDLController*);
		protected:
			VSDLController* fParentController;
			SDLWindow* fWindow;
	};
}

#endif
