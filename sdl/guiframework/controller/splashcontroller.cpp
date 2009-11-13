#include <SDL/SDL.h>

#include "guiframework/controller/splashcontroller.h"

#include <iostream>

namespace sdlframework {

	SplashController::SplashController(SDLWindow* window, std::string fileName) : VSDLController(window) {
		SDL_Surface *temp;
		temp = SDL_LoadBMP(("../data/"+fileName).c_str());
		if (temp == NULL) {
			// What to do now?
			return;
		}
		
		fImageSurface = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
	}
	
	SplashController::SplashController(const SplashController& orig) : VSDLController(orig.fWindow)  {
	}
	
	SplashController::~SplashController() {	
		SDL_FreeSurface(fImageSurface);
	}
	
	void SplashController::draw() {
		fWindow->drawSurface(fImageSurface);
	}
}
