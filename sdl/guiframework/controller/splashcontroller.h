#ifndef INC_SPLASHCONTROLLER_H
#define INC_SPLASHCONTROLLER_H

#include <string>

#include "guiframework/controller/sdlcontroller.h"
#include "guiframework/resources/imageresource.h"

namespace sdlframework {

	class SplashController : public VSDLController {
	public:
		SplashController(SDLWindow*, std::string, VSDLController*);
		SplashController(const SplashController&);
		virtual ~SplashController();

		virtual void draw();
	private:
		ImageResource* fImage;
		VSDLController* fNextController;
		int i;
	};
}

#endif // INC_SPLASHCONTROLLER_H
