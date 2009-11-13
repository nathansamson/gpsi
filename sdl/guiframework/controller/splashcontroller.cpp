#include <SDL/SDL.h>

#include "guiframework/controller/splashcontroller.h"
#include "guiframework/resources/resourcemanager.h"

namespace sdlframework {

	SplashController::SplashController(SDLWindow* window, std::string fileName) : VSDLController(window) {
		fImage = ResourceManager::manager().image(fileName);
	}
	
	SplashController::SplashController(const SplashController& orig) : VSDLController(orig.fWindow)  {
	}
	
	SplashController::~SplashController() {
		ResourceManager::manager().free(fImage);
	}
	
	void SplashController::draw() {
		fWindow->drawImage(fImage, 0, 0);
	}
}
