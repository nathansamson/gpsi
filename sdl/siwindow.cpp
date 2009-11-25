#include <iostream>
#include "SDL.h"

#include "zabbr/sdlwindow.h"
#include "zabbr/controller/splashcontroller.h"
#include "zabbr/controller/menucontroller.h"
#include "zabbr/widgets/button.h"
#include "zabbr/widgets/label.h"
#include "siwindow.h"

namespace sisdl {
	
	/**
	 * Run the Space Invaders window.
	*/
	void SIWindow::run() {
		try {
			open(400, 300, false);
		} catch (SDLInitializationException e) {
			std::cerr << "Could not initialize SDL: " << e.getError() << std::endl;
			return;
		}

		try {
			MenuController* menu = new MenuController(this);
			SDL_Color c = {255, 255, 255};
			menu->addWidget(new Label(this, "Sprotector", c));
			menu->addWidget(new Button(this, "My Shiny Button"));
			menu->addWidget(new Button(this, "Another button"));
			Button* b = new Button(this, "Quit");
			b->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::confirmQuit));
			menu->addWidget(b);
	
			VSDLController* controller = new SplashController(this, "splash.bmp", menu);
			SDLWindow::run(controller);
		} catch (ResourceNotLoadedException& e) {
			std::cerr << "Could not load resource " << e.getResourceID() << " :" << e.getError() << std::endl;
		}
		close();
	}

	/**
	 * Callback when the quit button is clicked.
	 *
	 * @param e The Mouse Button Event.
	*/
	void SIWindow::onQuit(SDL_MouseButtonEvent e)
	{
		fController->quit();
	}

	/**
	 * Callback when the quit is canceled.
	 *
	 * @param e The Mouse Button Event.
	*/
	void SIWindow::cancelQuit(SDL_MouseButtonEvent e)
	{
		fController->openParentController();
		fController->foreground();
	}

	/**
	 * Callback when the quit is confirmed.
	 *
	 * @param e The Mouse Button Event.
	*/
	void SIWindow::confirmQuit(SDL_MouseButtonEvent e)
	{
		MenuController* quitConfirmation = new MenuController(this);
		Button* b = new Button(this, "Yes");
		b->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::onQuit));
		quitConfirmation->addWidget(b);
		b = new Button(this, "No");
		b->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::cancelQuit));
		quitConfirmation->addWidget(b);

		fController->background();
		fController->openController(quitConfirmation);
	}

	/**
	 * Constructor.
	 *
	 * @param window The SIWindow.
	 * @param fp The member pointer.
	*/
	SIWindowMouseButtonCallback::SIWindowMouseButtonCallback(
	       SIWindow* window, void (SIWindow::*fp)(SDL_MouseButtonEvent))
	                            : fWindow(window), fFunction(fp) {
	}

	/**
	 * Call the callback with specific parameter.
	 *
	 * @param e The SDL_MouseButtonEvent
	*/
	void SIWindowMouseButtonCallback::call(SDL_MouseButtonEvent e)
	{
		(fWindow->*fFunction)(e);
	}
}
