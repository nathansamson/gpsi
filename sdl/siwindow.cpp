#include <iostream>
#include "SDL.h"

#include "zabbr/sdlwindow.h"
#include "zabbr/controller/splashcontroller.h"
#include "zabbr/controller/menucontroller.h"
#include "zabbr/widgets/button.h"
#include "zabbr/widgets/label.h"
#include "zabbr/resources/resourcemanager.h"
#include "gamecontroller.h"
#include "siwindow.h"

namespace SISDL {
	
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
		
		setDataPath();

		try {
			MenuController* menu = new MenuController(this);
			SDL_Color c = {255, 255, 255};
			menu->addWidget(new Label(this, "Sprotector", c));
			
			Button* start = new Button(this, "Start game");
			start->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::startGame));
			menu->addWidget(start);
			
			menu->addWidget(new Button(this, "Another button"));
			
			Button* b = new Button(this, "Quit");
			b->connectOnMouseClick(new SIWindowMouseButtonCallback(this, &SIWindow::onQuitButtonClicked));
			menu->addWidget(b);
			
			menu->connectRequestQuit(new SIWindowEmptyCallback(this, &SIWindow::onRequestQuitMainMenu));
	
			VSDLController* controller = new SplashController(this, "splash.bmp", menu);
			SDLWindow::run(controller);
		} catch (ResourceNotLoadedException& e) {
			std::cerr << "Could not load resource " << e.getResourceID() << " :" << e.getError() << std::endl;
		}
		close();
	}

	/**
	 * Callback when the yes button in the quit confirmation dialog is clicked.
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
	void SIWindow::onQuitButtonClicked(SDL_MouseButtonEvent e)
	{
		fController->requestQuit();
	}
	
	/**
	 * Callback called when a quit is requested in the main menu.
	*/
	void SIWindow::onRequestQuitMainMenu() {
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
	 * Callback to start the game.
	*/
	void SIWindow::startGame(SDL_MouseButtonEvent e) {
		GameController* gameController = new GameController(this);
		
		fController->background();
		fController->openController(gameController);
	}

	/**
	 * Sets the data path of the manager.
	*/
	void SIWindow::setDataPath() {
		ResourceManager::fgDataPath = "./data/";
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
	
	/**
	 * Constructor.
	 *
	 * @param window The SIWindow.
	 * @param fp The member pointer.
	*/
	SIWindowEmptyCallback::SIWindowEmptyCallback(
	       SIWindow* window, void (SIWindow::*fp)())
	                            : fWindow(window), fFunction(fp) {
	}

	/**
	 * Call the callback with specific parameter.
	*/
	void SIWindowEmptyCallback::call()
	{
		(fWindow->*fFunction)();
	}
}
