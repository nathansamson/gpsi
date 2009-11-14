#include <SDL/SDL.h>

#include "guiframework/sdlwindow.h"
#include "guiframework/controller/splashcontroller.h"
#include "guiframework/controller/menucontroller.h"
#include "siwindow.h"

namespace sisdl {
	
	void SIWindow::run() {
		open(400, 300, false);
		
		MenuController* menu = new MenuController(this);
		VSDLController* controller = new SplashController(this, "splash.bmp", menu);
		SDLWindow::run(controller);
		close();
	}

}
