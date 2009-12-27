/** \file
 * File for the SI window.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include "SDL.h"

#include "zabbr/sdlwindow.h"
#include "zabbr/panels/splashpanel.h"
#include "zabbr/panels/widgetpanel.h"
#include "zabbr/panels/dialogpanel.h"
#include "zabbr/widgets/button.h"
#include "zabbr/widgets/label.h"
#include "zabbr/widgets/vbox.h"
#include "zabbr/resources/resourcemanager.h"
#include "zabbr/misc/fontprefetcher.h"
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
				SDL_Color white = {255, 255, 255};
				MenuPanel* menu = new MenuPanel(this, "/Space/ Invaders", white, "fonts/orbitron-black.ttf", 64);
				SplashPanel* splash = new SplashPanel(this, "splash.png", menu);
				FontPrefetcher* fontPrefetcher = new FontPrefetcher("Loading fonts...");
				fontPrefetcher->addFontSize(18);
				fontPrefetcher->addFontSize(24);
				fontPrefetcher->addFontSize(28);
				fontPrefetcher->addFontSize(34);
				fontPrefetcher->addFont("DejaVuSans-Bold.ttf");
				fontPrefetcher->addFont("fonts/Blackout-Midnight.ttf");
				fontPrefetcher->addFont("fonts/orbitron-black.ttf");
				splash->addPrefetcher(fontPrefetcher);
			
				Button* start = new Button(this, "Start game");
				start->connectOnMouseClick(new ClassCallback1<SIWindow, SDL_MouseButtonEvent>(this, &SIWindow::startGame));
				menu->addButton(start);
			
				menu->addButton(new Button(this, "Another button"));
			
				Button* b = new Button(this, "Quit");
				b->connectOnMouseClick(new ClassCallback1<SIWindow, SDL_MouseButtonEvent>(this, &SIWindow::onQuitButtonClicked));
				menu->addButton(b);
			
				menu->connectRequestQuit(new ClassCallback0<SIWindow>(this, &SIWindow::onRequestQuitMainMenu));
	
				SDLWindow::run(splash);
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
