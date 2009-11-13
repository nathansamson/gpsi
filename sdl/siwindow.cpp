#include <SDL/SDL.h>

#include "guiframework/sdlwindow.h"
#include "guiframework/controller/splashcontroller.h"
#include "siwindow.h"

namespace sisdl {
	
	void SIWindow::run() {
		open(400, 300, false);
		VSDLController* controller = new SplashController(this, "splash.bmp");
		
		SDL_Event event;
		bool running = true;

		while (running) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE)  {
							running = false;
						}
						break;
					case SDL_QUIT:
						running = false;
						break;
				}
			}
			controller->draw();
			draw();
			SDL_Delay(1);
		}
		close();
		
		delete controller;
	}

}
