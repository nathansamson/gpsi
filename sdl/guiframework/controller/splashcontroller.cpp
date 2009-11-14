#include <SDL/SDL.h>

#include "guiframework/controller/splashcontroller.h"
#include "guiframework/resources/resourcemanager.h"

namespace sdlframework {

	SplashController::SplashController(SDLWindow* window,
	          std::string fileName, VSDLController* controller) 
	          : VSDLController(window), fNextController(controller) {
		fImage = ResourceManager::manager().image(fileName);
		i = 0;
	}
	
	SplashController::SplashController(const SplashController& orig) : VSDLController(orig.fWindow)  {
	}
	
	SplashController::~SplashController() {
		ResourceManager::manager().free(fImage);
	}
	
	void SplashController::draw() {
		fWindow->drawImage(fImage, 0, 0);
		SDL_Delay(1000);
		i++;
		if (i > 5) {
			fWindow->closeController(fNextController);
		}
	}
}
