#include "SDL.h"

#include "controller/splashcontroller.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The SDLWindow.
	 * @param fileName The file name of the splash image.
	 * @param controller The controller that should be activated after loading is done.
	*/
	SplashController::SplashController(
	          SDLWindow* window, std::string fileName,
	          VSDLController* controller)
	                : VSDLController(window),
	                  fNextController(controller) {
		fImage = ResourceManager::manager().image(fileName);
		i = 0;
	}
	
	/**
	 * Desctructor.
	*/
	SplashController::~SplashController() {
		ResourceManager::manager().free(fImage);
	}
	
	/**
	 * Draws the splash screen.
	*/
	void SplashController::draw() {
		fWindow->drawImage(fImage, 0, 0);
		SDL_Delay(1000);
		i++;
		if (i > 2) {
			fWindow->closeController(fNextController);
		}
	}
}