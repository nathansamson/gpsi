#include "guiframework/controller/menucontroller.h"

namespace sdlframework {

	MenuController::MenuController(SDLWindow* window)  : VSDLController(window) {
	}
	
	MenuController::MenuController(const MenuController& orig) : VSDLController(orig.fWindow)  {
	}
	
	MenuController::~MenuController() {
	}

	void MenuController::addWidget(VWidget* widget) {
		fWidgets.push_back(widget);
	}
	
	void MenuController::draw() {
		int y = 0;
		int x = 200;
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->draw(x, y);
			y += (*it)->getHeight();
		}
	}
	
	void MenuController::keyDown(SDL_KeyboardEvent key) {
		if (key.keysym.sym == SDLK_ESCAPE) {
			fWindow->closeController(NULL);
		}
	}

	void MenuController::mouseMotion(SDL_MouseMotionEvent event) {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseMotion(event);
		}
	}
	
	void MenuController::quit() {
		fWindow->closeController(NULL);
	}
}
