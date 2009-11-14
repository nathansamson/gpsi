#include "guiframework/controller/menucontroller.h"

namespace sdlframework {

	MenuController::MenuController(SDLWindow* window)  : VSDLController(window) {
	}
	
	MenuController::MenuController(const MenuController& orig) : VSDLController(orig.fWindow)  {
	}
	
	MenuController::~MenuController() {
	}
	
	void MenuController::draw() {
		fWindow->drawRectangle(0, 0, 40, 200, 255, 0, 0);
	}
	
	void MenuController::keyDown(SDL_KeyboardEvent key) {
		if (key.keysym.sym == SDLK_ESCAPE) {
			fWindow->closeController(NULL);
		}
	}
	
	void MenuController::quit() {
		fWindow->closeController(NULL);
	}
}
