#ifndef _SDLCONTROLLER_H_
#define _SDLCONTROLLER_H_

#include "guiframework/sdlwindow.h"

namespace sdlframework {
	class VSDLController {
		public:
			VSDLController(SDLWindow* window);
			virtual ~VSDLController();
			
			virtual void draw() = 0;
		protected:
			SDLWindow* fWindow;
	};
}

#endif
