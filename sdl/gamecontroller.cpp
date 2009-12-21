#include "zabbr/widgets/button.h"
#include "zabbr/events/callbacks.h"
#include "zabbr/resources/resourcemanager.h"

#include "gamecontroller.h"
#include "sdlentityfactory.h"
#include "sdlkeyboardinputdriver.h"
#include "sdldriverfactory.h"

namespace SISDL {
	/**
	 * Public constructor
	 *
	 * @param w The Window
	*/
	GameController::GameController(Zabbr::SDLWindow* w): Zabbr::VSDLController(w),
	                fGame(0), fTimeRemainder(0.0), fClosed(false) {
		startGame();
		connectRequestQuit(new Zabbr::ClassCallback0<GameController>(this, &GameController::onRequestQuitGame));
	}
	
	/**
	 * Destructor;
	*/
	GameController::~GameController() {
		delete fGame;
	}
	
	/**
	 * Draws the controller.
	*/
	void GameController::draw() {
		if (fClosed) {
			openParentController();
		}
		
		if (!fTimer.isPaused()) {
			double time = fTimer.reset();
			int ticks = (time + fTimeRemainder) * 1000;
			fTimeRemainder = ((time + fTimeRemainder) * 1000 - ticks) / 1000;
		
			fGame->update(ticks);
		} else {
			fGame->update(0); // Let the entities draw themselves.
		}
	}
	
	/**
	 * Method called by the window if a key is pressed.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void GameController::keyPress(SDL_KeyboardEvent evnt) {
		fGameVisualizer->keyPress(evnt);
		fInputDriver = fDriverFactory->getUserDriver();
		if (!fGame->isUserDead()) fInputDriver->keyDown(evnt);
	}
	
	/**
	 * Method called by the window if a key is released.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void GameController::keyRelease(SDL_KeyboardEvent evnt) {
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
				fClosed = true; // Return to parent controller.
			}
		}
	}
	
	/**
	 * Method callback that is called when the controller is requested to quit.
	*/
	void GameController::onRequestQuitGame() {
		fTimer.pause();
		fQuitConfirmation = new Zabbr::MenuController(fWindow);
		Zabbr::Button* b = new Zabbr::Button(fWindow, "Resume game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<GameController, SDL_MouseButtonEvent>(this, &GameController::onResumeGame));
		fQuitConfirmation->addWidget(b);

		b = new Zabbr::Button(fWindow, "Quit Game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<GameController, SDL_MouseButtonEvent>(this, &GameController::onQuitGame));
		fQuitConfirmation->addWidget(b);
		
		b = new Zabbr::Button(fWindow, "Close game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<GameController, SDL_MouseButtonEvent>(this, &GameController::onCloseGame));
		fQuitConfirmation->addWidget(b);

		openController(fQuitConfirmation);
	}
	
	/**
	 * Resume game callback.
	*/
	void GameController::onResumeGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->openParentController();
		fTimer.unpause();
	}
	
	/**
	 * Quit game callback.
	*/
	void GameController::onQuitGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->openParentController();
		fClosed = true;
		//fController->openParentParentController();
	}
	
	/**
	 * Close game callback.
	*/
	void GameController::onCloseGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->quit();
	}
	
	void GameController::startGame() {
		fGameVisualizer = new SDLGameVisualizer(fWindow);
		fDriverFactory = new SDLDriverFactory();
		fGame = new SI::Game(new SDLEntityFactory(fWindow),
		                     "data/levels/", "firstlevel.silvl",
		                     fGameVisualizer, fDriverFactory);
	}
}
