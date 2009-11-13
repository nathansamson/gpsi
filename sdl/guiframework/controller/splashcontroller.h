#ifndef _SPLASHCONTROLLER_H_
#define _SPLASHCONTROLLER_H_

#include <string>

#include "guiframework/controller/sdlcontroller.h"

namespace sdlframework {
	class SplashController : public VSDLController {
		public:
			SplashController(SDLWindow*, std::string);
			SplashController(const SplashController&);
			virtual ~SplashController();
		
			virtual void draw();
		private:
			SDL_Surface* fImageSurface;
	};
}

#endif
