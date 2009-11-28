#include "zabbr/widgets/button.h"

#include "gamecontroller.h"
#include "sdlentityfactory.h"
#include "sdlkeyboardinputdriver.h"

namespace SISDL {
	/**
	 * Public constructor
	 *
	 * @param w The Window
	*/
	GameController::GameController(Zabbr::SDLWindow* w): Zabbr::VSDLController(w),
	                fGame(0), fTimeRemainder(0.0), fClosed(false) {
		fInputDriver = new SDLKeyboardInputDriver();
		fGame = new SI::Game(fInputDriver, new SDLEntityFactory(w));
		connectRequestQuit(new GameControllerEmptyCallback(this, &GameController::onRequestQuitGame));
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
		double time = fTimer.reset();
		int ticks = (time + fTimeRemainder) * 1000;
		fTimeRemainder = (time + fTimeRemainder) * 1000 - ticks;
		
		fGame->update(ticks);
	}
	
	/**
	 * Method called by the window if a key is pressed.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void GameController::keyDown(SDL_KeyboardEvent evnt) {
		fInputDriver->keyDown(evnt);
	}
	
	/**
	 * Method called by the window if a key is released.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void GameController::keyRelease(SDL_KeyboardEvent evnt) {
		fInputDriver->keyRelease(evnt);
		if (evnt.keysym.sym == SDLK_ESCAPE) {
			requestQuit();
		}
	}
	
	/**
	 * Method callback that is called when the controller is requested to quit.
	*/
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
	 * @param c The GameController.
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
	 * @param c The GameController.
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
