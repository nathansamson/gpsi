/** \file
 * File for the SI window.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include "SDL.h"

#include "zabbr/sdlwindow.h"
#include "zabbr/panels/splashpanel.h"
#include "zabbr/panels/menupanel.h"
#include "zabbr/panels/dialogpanel.h"
#include "zabbr/widgets/button.h"
#include "zabbr/widgets/label.h"
#include "zabbr/resources/resourcemanager.h"
#include "normalgamepanel.h"
#include "demogamepanel.h"
#include "siwindow.h"

namespace SISDL {

	/**
	 * Run the space invaders window in demo mode.
	*/
	
	void SIWindow::rundemo() {
		try {
			open(640, 480, false);
		} catch (SDLInitializationException e) {
			std::cerr << "Could not initialize SDL: " << e.getError() << std::endl;
			return;
		}
		
		setDataPath();

		try {
			SDLWindow::run(new DemoGamePanel(this));
		} catch (ResourceNotLoadedException& e) {
			std::cerr << "Could not load resource " << e.getResourceID() << " :" << e.getError() << std::endl;
		}
		close();
	}
	
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
				MenuPanel* menu = new MenuPanel(this);
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
	
				VSDLPanel* controller = new SplashPanel(this, "splash.png", menu);
				SDLWindow::run(controller);
			} else {
				SDLWindow::run(new NormalGamePanel(this));
			}
		} catch (ResourceNotLoadedException& e) {
			std::cerr << "Could not load resource " << e.getResourceID() << " :" << e.getError() << std::endl;
		}
		close();
	}

	/**
	 * Callback when the quit is confirmed.
	 *
	 * @param e The Mouse Button Event.
	*/
	void SIWindow::onQuitButtonClicked(SDL_MouseButtonEvent e)
	{
		fPanel->requestQuit();
	}
	
	/**
	 * Callback called when a quit is requested in the main menu.
	*/
	void SIWindow::onRequestQuitMainMenu() {
		std::vector<std::pair<int, std::string> > responseIDs;
		responseIDs.push_back(std::pair<int, std::string>(0, "No"));
		responseIDs.push_back(std::pair<int, std::string>(1, "Yes"));
		DialogPanel* quitConfirmation = new DialogPanel(this, "Are you sure you want to quit?", responseIDs);
		quitConfirmation->connectOnResponse(new ClassCallback1<SIWindow, int>(this, &SIWindow::onQuitConfirmationResponse));

		fPanel->openPanel(quitConfirmation);
	}
	
	/**
	 * Callback when the quit confirmation responds.
	 *
	 * @param response The response ID.
	*/
	void SIWindow::onQuitConfirmationResponse(int response) {
		if (response == 0) {
			fPanel->openParentPanel();
		} else {
			fPanel->quit();
		}
	}
	
	/**
	 * Callback to start the game.
	*/
	void SIWindow::startGame(SDL_MouseButtonEvent e) {
		fPanel->openPanel(new NormalGamePanel(this));
	}

	/**
	 * Sets the data path of the manager.
	*/
	void SIWindow::setDataPath() {
		ResourceManager::fgDataPath = "./data/";
	}
}
