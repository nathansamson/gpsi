#include <iostream>
#include "SDL.h"

#include "guiframework/sdlwindow.h"
#include "guiframework/controller/splashcontroller.h"
#include "guiframework/controller/menucontroller.h"
#include "guiframework/widgets/button.h"
#include "siwindow.h"

namespace sisdl {
	
	void SIWindow::run() {
		try {
			open(400, 300, false);
		} catch (SDLInitializationException e) {
			std::cerr << "Could not initialize SDL: " << e.getError() << std::endl;
			return;
		}
		
		MenuController* menu = new MenuController(this);
		menu->addWidget(new Button(this, "My Shiny Button"));
		menu->addWidget(new Button(this, "Another button"));
		Button* b = new Button(this, "Quit");
		b->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::confirmQuit));
		menu->addWidget(b);

		VSDLController* controller = new SplashController(this, "splash.bmp", menu);
		SDLWindow::run(controller);
		close();
	}

	void SIWindow::onQuit(SDL_MouseButtonEvent e)
	{
		fController->quit();
	}

	void SIWindow::cancelQuit(SDL_MouseButtonEvent e)
	{
		fController->openParentController();
	}

	void SIWindow::confirmQuit(SDL_MouseButtonEvent e)
	{
		MenuController* quitConfirmation = new MenuController(this);
		Button* b = new Button(this, "Yes");
		b->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::onQuit));
		quitConfirmation->addWidget(b);
		b = new Button(this, "No");
		b->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::cancelQuit));
		quitConfirmation->addWidget(b);

		fController->openController(quitConfirmation);
	}

	SIWindowMouseButtonCallback::SIWindowMouseButtonCallback(SIWindow* window, void (SIWindow::*fp)(SDL_MouseButtonEvent)) : fWindow(window), fFunction(fp) {
	}

	void SIWindowMouseButtonCallback::call(SDL_MouseButtonEvent e)
	{
		(fWindow->*fFunction)(e);
	}
}
