#include "zabbr/controller/sdlcontroller.h"
#include "zabbr/controller/menucontroller.h"
#include "zabbr/misc/stopwatch.h"
#include "src/game/game.h"

#include "sdlinputdriver.h"

namespace SISDL {
	
	class GameController: public Zabbr::VSDLController {
	public:
		GameController(Zabbr::SDLWindow*);
		virtual ~GameController();
	
		virtual void draw();
		virtual void keyDown(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
		
		void onRequestQuitGame();
		void onResumeGame(SDL_MouseButtonEvent);
		void onQuitGame(SDL_MouseButtonEvent);
		void onCloseGame(SDL_MouseButtonEvent);
	private:
		SI::Game* fGame;
		SDLInputDriver* fInputDriver;
		Zabbr::Stopwatch fTimer;
		double fTimeRemainder;
		
		Zabbr::MenuController* fQuitConfirmation;
		bool fClosed;
	};
	
	/**
	 * GameController window empty callback.
	*/
	class GameControllerEmptyCallback: public Zabbr::IEmptyCallback {
	public:
		GameControllerEmptyCallback(GameController*, void (GameController::*)());
		virtual void call();
	private:
		/**
		 * The attached game controller.
		*/
		GameController* fGameController;
		/**
		 * The attached member function.
		*/
		void (GameController::* fFunction)();
	};
	
	/**
	 * GameController window mouse button callback.
	*/
	class GameControllerMouseButtonCallback: public Zabbr::IMouseButtonCallback {
	public:
		GameControllerMouseButtonCallback(GameController*, void (GameController::*)(SDL_MouseButtonEvent));
		virtual void call(SDL_MouseButtonEvent);
	private:
		/**
		 * The attached game controller.
		*/
		GameController* fGameController;
		/**
		 * The attached member function.
		*/
		void (GameController::* fFunction)(SDL_MouseButtonEvent);
	};
}
