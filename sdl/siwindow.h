#ifndef INC_SIWINDOW_H
#define INC_SIWINDOW_H

/** \file
 * File for the SI window.
 *
 * @author Nathan Samson
*/

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
		void rundemo();

		void onQuitButtonClicked(SDL_MouseButtonEvent);
		void onRequestQuitMainMenu();
		void onQuitConfirmationResponse(int);
		
		void startGame(SDL_MouseButtonEvent);
	private:
		void setDataPath();
		
		void onMainMenuKeyRelease(Zabbr::VSDLPanel*, SDL_KeyboardEvent);
	};
}

#endif // INC_SIWINDOW_H
