/** \file
 * File for the SI window.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include <stdexcept>
#include "SDL.h"

#include "zabbr/sdlwindow.h"
#include "zabbr/panels/splashpanel.h"
#include "zabbr/panels/widgetpanel.h"
#include "zabbr/panels/dialogpanel.h"
#include "zabbr/widgets/label.h"
#include "zabbr/widgets/vbox.h"
#include "zabbr/resources/resourcemanager.h"
#include "zabbr/misc/fontprefetcher.h"
#ifdef ENABLE_AUDIO
#include "zabbr/misc/soundprefetcher.h"
#include "zabbr/misc/musicprefetcher.h"
#endif
#include "zabbr/misc/audiomanager.h"
#include "normalgamepanel.h"
#include "demogamepanel.h"
#include "optionspanel.h"
#include "configurationmanager.h"
#include "siwindow.h"

namespace SISDL {

	SIWindow::SIWindow(): SDLWindow("Space-Invaders") {
	}

	/**
	 * Run the space invaders window in demo mode.
	*/
	void SIWindow::rundemo() {
		try {
			open(640, 480, false);
			
			setDataPath();
		} catch (SDLInitializationException e) {
			std::cerr << "Could not initialize SDL: " << e.getError() << std::endl;
			return;
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			return;
		}

		try {
			runSplashPanel(new DemoGamePanel(this));
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
			open(ConfigurationManager::getOption<int>("xres", 640),
			     ConfigurationManager::getOption<int>("yres", 480),
			     ConfigurationManager::getOption("fullscreen", false), true, 4.0/3.0);
			
			setDataPath();
		} catch (SDLInitializationException e) {
			std::cerr << "Could not initialize SDL: " << e.getError() << std::endl;
			return;
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			return;
		}

		try {
			VSDLPanel* panel;
			if (!game) {
				SDL_Color white = {255, 255, 255};
				MenuPanel* menu = new MenuPanel(this, "/Space/ Invaders", white, "fonts/orbitron-black.ttf", 64);
			
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
				menu->connectOnKeyPress(new ClassCallback2<SIWindow, Zabbr::VSDLPanel*, SDL_KeyboardEvent>(this, &SIWindow::onMainMenuKeyPress));
				
				panel = menu;
			} else {
				panel = new NormalGamePanel(this);
			}
			
			runSplashPanel(panel);
		} catch (ResourceNotLoadedException& e) {
			std::cerr << "Could not load resource " << e.getResourceID() << " :" << e.getError() << std::endl;
		}
		close();
	}
	
	void SIWindow::runSplashPanel(VSDLPanel* panel) {
		SplashPanel* splash = new SplashPanel(this, "splash.png", panel);
		FontPrefetcher* fontPrefetcher = new FontPrefetcher("Loading fonts...");
		fontPrefetcher->addFontSize(18);
		fontPrefetcher->addFontSize(24);
		fontPrefetcher->addFontSize(28);
		fontPrefetcher->addFontSize(34);
		fontPrefetcher->addFont("DejaVuSans-Bold.ttf");
		fontPrefetcher->addFont("fonts/Blackout-Midnight.ttf");
		fontPrefetcher->addFont("fonts/orbitron-black.ttf");
		splash->addPrefetcher(fontPrefetcher);
	
		#ifdef ENABLE_AUDIO
		SoundPrefetcher* soundFetch = new SoundPrefetcher("Loading sounds...");
		soundFetch->addSound("sounds/explosion.ogg");
		soundFetch->addSound("sounds/firebullet.ogg");
		soundFetch->addSound("sounds/clusterbomb.ogg");
		splash->addPrefetcher(soundFetch);
	
		if (ConfigurationManager::getOption("play-music", false)) {
			MusicPrefetcher* musicFetch = new MusicPrefetcher("Loading music");
			musicFetch->addMusic("music/AC SPACE.mp3");
			splash->addPrefetcher(musicFetch);
		}
	
		splash->connectOnClosePanel(new ClassCallback1<SIWindow, VSDLPanel*>(this, &SIWindow::startMusic));
		#endif
		
		SDLWindow::run(splash);
	}
	
	void SIWindow::startMusic(VSDLPanel*) {
		AudioManager::get().addMusicFile("music/AC SPACE.mp3");
		if (ConfigurationManager::getOption("play-music", false)) {
			AudioManager::get().startMusic();
		}
		if (!ConfigurationManager::getOption("play-sound", true)) {
			AudioManager::get().mute();
		} else {
			AudioManager::get().unmute();
		}
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
					throw std::runtime_error("No data path found.");
				}
			}
		}
	}
	
	void SIWindow::onMainMenuKeyPress(Zabbr::VSDLPanel* panel, SDL_KeyboardEvent event) {
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
