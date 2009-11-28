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
		void confirmQuit(SDL_MouseButtonEvent);
		void cancelQuit(SDL_MouseButtonEvent);
		
		void startGame(SDL_MouseButtonEvent);
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

}

#endif // INC_SIWINDOW_H
