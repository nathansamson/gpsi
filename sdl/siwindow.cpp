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
	 *
	 * @param game True if should run without menu and splash screen.
	*/
	void SIWindow::run(bool game) {
		try {
			open(640, 480, false);
		} catch (SDLInitializationException e) {
			std::cerr << "Could not initialize SDL: " << e.getError() << std::endl;
			return;
		}
		
		setDataPath();

		try {
			if (!game) {
				MenuController* menu = new MenuController(this);
				SDL_Color c = {255, 255, 255};
				menu->addWidget(new Label(this, "/Space/ Invaders", c, "fonts/orbitron-black.ttf", 64));
			
				Button* start = new Button(this, "Start game");
				start->connectOnMouseClick(new ClassCallback1<SIWindow, SDL_MouseButtonEvent>(this, &SIWindow::startGame));
				menu->addWidget(start);
			
				menu->addWidget(new Button(this, "Another button"));
			
				Button* b = new Button(this, "Quit");
				b->connectOnMouseClick(new ClassCallback1<SIWindow, SDL_MouseButtonEvent>(this, &SIWindow::onQuitButtonClicked));
				menu->addWidget(b);
			
				menu->connectRequestQuit(new ClassCallback0<SIWindow>(this, &SIWindow::onRequestQuitMainMenu));
	
				VSDLController* controller = new SplashController(this, "splash.png", menu);
				SDLWindow::run(controller);
			} else {
				SDLWindow::run(new GameController(this));
			}
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
		b->connectOnMouseClick(new ClassCallback1<SIWindow, SDL_MouseButtonEvent>(this, &SIWindow::onQuit));
		quitConfirmation->addWidget(b);
		b = new Button(this, "No");
		b->connectOnMouseClick(new ClassCallback1<SIWindow, SDL_MouseButtonEvent>(this, &SIWindow::cancelQuit));
		quitConfirmation->addWidget(b);

		fController->openController(quitConfirmation);
	}
	
	/**
	 * Callback to start the game.
	*/
	void SIWindow::startGame(SDL_MouseButtonEvent e) {
		GameController* gameController = new GameController(this);
		
		fController->openController(gameController);
	}

	/**
	 * Sets the data path of the manager.
	*/
	void SIWindow::setDataPath() {
		ResourceManager::fgDataPath = "./data/";
	}
}
