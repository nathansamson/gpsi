#include <sstream>

#include "zabbr/widgets/button.h"
#include "zabbr/events/callbacks.h"
#include "zabbr/resources/resourcemanager.h"

#include "gamepanel.h"
#include "highscorepanel.h"
#include "sdlentityfactory.h"
#include "sdlkeyboardinputdriver.h"
#include "sdldriverfactory.h"

namespace SISDL {

	/**
	 * Public constructor
	 *
	 * @param w The Window
	*/
	GamePanel::GamePanel(Zabbr::SDLWindow* w): Zabbr::VSDLPanel(w),
	                fGame(0), fTimeRemainder(0.0), fClosed(false) {
		startGame();
		connectRequestQuit(new Zabbr::ClassCallback0<GamePanel>(this, &GamePanel::onRequestQuitGame));
		fFont = Zabbr::ResourceManager::manager().font("DejaVuSans-Bold.ttf", 18);
	}
	
	/**
	 * Destructor;
	*/
	GamePanel::~GamePanel() {
		delete fGame;
		delete fGameVisualizer;
		Zabbr::ResourceManager::manager().free(fFont);
	}
	
	/**
	 * Draws the panel.
	*/
	void GamePanel::draw() {
		if (fClosed && !fIsBackground) {
			openParentPanel();
		}
		
		if (!fTimer.isPaused()) {
			double time = fTimer.reset();
			int ticks = (time + fTimeRemainder) * 1000;
			fTimeRemainder = ((time + fTimeRemainder) * 1000 - ticks) / 1000;
		
			fGame->update(ticks);
		} else {
			fGame->update(0); // Let the entities draw themselves.
		}
		SDL_Color white = {255, 255, 255};
		std::stringstream ssScoreText;
		ssScoreText << fGame->getUserScore();
		std::string scoreText;
		ssScoreText >> scoreText;
		fScoreText = Zabbr::ResourceManager::manager().string(scoreText, fFont, white);
		fWindow->drawSurface(fScoreText, 10, 10);
		Zabbr::ResourceManager::manager().free(fScoreText);
	}
	
	/**
	 * Method called by the window if a key is pressed.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void GamePanel::keyPress(SDL_KeyboardEvent evnt) {
		fGameVisualizer->keyPress(evnt);
		fInputDriver = fDriverFactory->getUserDriver();
		if (!fGame->isUserDead()) fInputDriver->keyDown(evnt);
	}
	
	/**
	 * Method called by the window if a key is released.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void GamePanel::keyRelease(SDL_KeyboardEvent evnt) {
		fInputDriver = fDriverFactory->getUserDriver();
		if (!fGame->isUserDead()) fInputDriver->keyRelease(evnt);
		if (evnt.keysym.sym == SDLK_ESCAPE) {
			requestQuit();
		} else if (evnt.keysym.sym == SDLK_RETURN) {
			if (!fGame->isPlaying()) {
				// TODO: Show a menu to choose what to do
				
				// Play new game
				// Go to main menu
				// Quit
				fClosed = true; // Return to parent panel.
				openPanel(new HighscorePanel(fWindow, fGame->getUserScore()));
			}
		}
	}
	
	/**
	 * Method callback that is called when the panel is requested to quit.
	*/
	void GamePanel::onRequestQuitGame() {
		fTimer.pause();
		fQuitConfirmation = new Zabbr::MenuPanel(fWindow);
		Zabbr::Button* b = new Zabbr::Button(fWindow, "Resume game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<GamePanel, SDL_MouseButtonEvent>(this, &GamePanel::onResumeGame));
		fQuitConfirmation->addWidget(b);

		b = new Zabbr::Button(fWindow, "Quit Game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<GamePanel, SDL_MouseButtonEvent>(this, &GamePanel::onQuitGame));
		fQuitConfirmation->addWidget(b);
		
		b = new Zabbr::Button(fWindow, "Close game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<GamePanel, SDL_MouseButtonEvent>(this, &GamePanel::onCloseGame));
		fQuitConfirmation->addWidget(b);

		openPanel(fQuitConfirmation);
	}
	
	/**
	 * Resume game callback.
	*/
	void GamePanel::onResumeGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->openParentPanel();
		fTimer.unpause();
	}
	
	/**
	 * Quit game callback.
	*/
	void GamePanel::onQuitGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->openParentPanel();
		fClosed = true;
		openPanel(new HighscorePanel(fWindow, fGame->getUserScore()));
	}
	
	/**
	 * Close game callback.
	*/
	void GamePanel::onCloseGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->quit();
	}
	
	/**
	 * Start a new game.
	*/
	void GamePanel::startGame() {
		fGameVisualizer = new SDLGameVisualizer(fWindow);
		fDriverFactory = new SDLDriverFactory();
		fGame = new SI::Game(new SDLEntityFactory(fWindow),
		                     "data/levels/", "firstlevel.silvl",
		                     fGameVisualizer, fDriverFactory);
	}
}
