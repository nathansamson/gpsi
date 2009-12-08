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
		void run(bool);

		void onQuit(SDL_MouseButtonEvent);
		void cancelQuit(SDL_MouseButtonEvent);
		void onQuitButtonClicked(SDL_MouseButtonEvent);
		void onRequestQuitMainMenu();
		
		void startGame(SDL_MouseButtonEvent);
	private:
		void setDataPath();
	};
}

#endif // INC_SIWINDOW_H
