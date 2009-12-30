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
#include "zabbr/widgets/label.h"
#include "zabbr/widgets/vbox.h"
#include "zabbr/resources/resourcemanager.h"
#include "zabbr/misc/fontprefetcher.h"
#include "normalgamepanel.h"
#include "demogamepanel.h"
#include "optionspanel.h"
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
			open(640, 480, false, true);
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
			
				Button* options = new Button(this, "Options"); 
				menu->addButton(options);
				options->connectOnClicked(new ClassCallback1<SIWindow, Button*>(this, &SIWindow::onOpenOptions));
			
				Button* quit = new Button(this, "Quit");
				quit->connectOnMouseClick(new ClassCallback1<SIWindow, SDL_MouseButtonEvent>(this, &SIWindow::onQuitButtonClicked));
				menu->addButton(quit);
			
				menu->connectRequestQuit(new ClassCallback0<SIWindow>(this, &SIWindow::onRequestQuitMainMenu));
				menu->connectOnKeyRelease(new ClassCallback2<SIWindow, Zabbr::VSDLPanel*, SDL_KeyboardEvent>(this, &SIWindow::onMainMenuKeyRelease));
	
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
		responseIDs.push_back(std::pair<int, std::string>(Zabbr::DialogPanel::Cancel, "No"));
		responseIDs.push_back(std::pair<int, std::string>(Zabbr::DialogPanel::Quit, "Yes"));
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
		if (response == Zabbr::DialogPanel::Cancel) {
			fPanel->openParentPanel();
		} else if (response == Zabbr::DialogPanel::Quit) {
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
		FILE* phony = fopen("./data/splash.png", "r");
		if (phony) {
			ResourceManager::fgDataPath = "./data/";
			fclose(phony);
		} else {
			phony = fopen("/usr/local/share/gpsi/splash.png", "r");
			if (phony) {
				ResourceManager::fgDataPath = "/usr/local/share/gpsi/";
				fclose(phony);
			} else {
				phony = fopen("/usr/share/gpsi/splash.png", "r");
				if (phony) {
					ResourceManager::fgDataPath = "/usr/share/gpsi/";
					fclose(phony);
				} else {
					throw 1234; // Who needs exceptions anyway?
				}
			}
		}
	}
	
	void SIWindow::onMainMenuKeyRelease(Zabbr::VSDLPanel* panel, SDL_KeyboardEvent event) {
		if (event.keysym.sym == SDLK_ESCAPE) {
			panel->requestQuit();
		}
	}
	
	/**
	 * Callback when clicked on the options button.
	*/
	void SIWindow::onOpenOptions(Zabbr::Button*) {
		fPanel->openPanel(new OptionsPanel(this));
	}
}
