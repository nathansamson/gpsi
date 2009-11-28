#ifndef INC_SIWINDOW_H
#define INC_SIWINDOW_H

#include "zabbr/sdlwindow.h"
#include "zabbr/events/callbacks.h"

namespace SISDL {
	using namespace Zabbr;


	/**
	 * Space Invaders window.
	*/
	class SIWindow : public  SDLWindow {
	public:
		void run();

		void onQuit(SDL_MouseButtonEvent);
		void cancelQuit(SDL_MouseButtonEvent);
		void onQuitButtonClicked(SDL_MouseButtonEvent);
		void onRequestQuitMainMenu();
		
		void startGame(SDL_MouseButtonEvent);
	private:
		void setDataPath();
	};

	/**
	 * Space Invaders window mouse button callback.
	*/
	class SIWindowMouseButtonCallback : public IMouseButtonCallback {
	public:
		SIWindowMouseButtonCallback(SIWindow*, void (SIWindow::*)(SDL_MouseButtonEvent));
		virtual void call(SDL_MouseButtonEvent);
	private:
		/**
		 * The attached window.
		*/
		SIWindow* fWindow;
		/**
		 * The attached member function.
		*/
		void (SIWindow::* fFunction)(SDL_MouseButtonEvent);
	};
	
	/**
	 * Space Invaders window empty callback.
	*/
	class SIWindowEmptyCallback: public IEmptyCallback {
	public:
		SIWindowEmptyCallback(SIWindow*, void (SIWindow::*)());
		virtual void call();
	private:
		/**
		 * The attached window.
		*/
		SIWindow* fWindow;
		/**
		 * The attached member function.
		*/
		void (SIWindow::* fFunction)();
	};

}

#endif // INC_SIWINDOW_H
