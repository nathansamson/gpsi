#include "zabbr/widgets/button.h"

#include "gamecontroller.h"
#include "sdlentityfactory.h"
#include "sdlkeyboardinputdriver.h"

namespace SISDL {
	GameController::GameController(Zabbr::SDLWindow* w): Zabbr::VSDLController(w),
	                fGame(0), fTimeRemainder(0.0), fClosed(false) {
		fInputDriver = new SDLKeyboardInputDriver();
		fGame = new SI::Game(fInputDriver, new SDLEntityFactory(w));
		connectRequestQuit(new GameControllerEmptyCallback(this, &GameController::onRequestQuitGame));
	}
	
	GameController::~GameController() {
		delete fGame;
	}
	
	void GameController::draw() {
		if (fClosed) {
			openParentController();
		}
		double time = fTimer.reset();
		int ticks = (time + fTimeRemainder) * 1000;
		fTimeRemainder = (time + fTimeRemainder) * 1000 - ticks;
		
		fGame->update(ticks);
	}
	
	void GameController::keyDown(SDL_KeyboardEvent evnt) {
		fInputDriver->keyDown(evnt);
	}
	
	void GameController::keyRelease(SDL_KeyboardEvent evnt) {
		fInputDriver->keyRelease(evnt);
	}
	
	void GameController::onRequestQuitGame() {
		fQuitConfirmation = new Zabbr::MenuController(fWindow);
		Zabbr::Button* b = new Zabbr::Button(fWindow, "Resume game");
		b->connectOnMouseClick(new GameControllerMouseButtonCallback(this, &GameController::onResumeGame));
		fQuitConfirmation->addWidget(b);

		b = new Zabbr::Button(fWindow, "Quit Game");
		b->connectOnMouseClick(new GameControllerMouseButtonCallback(this, &GameController::onQuitGame));
		fQuitConfirmation->addWidget(b);
		
		b = new Zabbr::Button(fWindow, "Close game");
		b->connectOnMouseClick(new GameControllerMouseButtonCallback(this, &GameController::onCloseGame));
		fQuitConfirmation->addWidget(b);

		background();
		openController(fQuitConfirmation);
	}
	
	/**
	 * Resume game callback.
	*/
	void GameController::onResumeGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->openParentController();
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
	
	/**
	 * Constructor.
	 *
	 * @param window The SIWindow.
	 * @param fp The member pointer.
	*/
	GameControllerEmptyCallback::GameControllerEmptyCallback(
	       GameController* c, void (GameController::*fp)())
	                            : fGameController(c), fFunction(fp) {
	}

	/**
	 * Call the callback with specific parameter.
	*/
	void GameControllerEmptyCallback::call()
	{
		(fGameController->*fFunction)();
	}
	
	/**
	 * Constructor.
	 *
	 * @param window The SIWindow.
	 * @param fp The member pointer.
	*/
	GameControllerMouseButtonCallback::GameControllerMouseButtonCallback(
	       GameController* c, void (GameController::*fp)(SDL_MouseButtonEvent))
	                            : fGameController(c), fFunction(fp) {
	}

	/**
	 * Call the callback with specific parameter.
	 *
	 * @param e The SDL_MouseButtonEvent
	*/
	void GameControllerMouseButtonCallback::call(SDL_MouseButtonEvent e)
	{
		(fGameController->*fFunction)(e);
	}
}
