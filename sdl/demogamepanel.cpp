/** \file
 * File for the SDL game panel.
 *
 * @author Nathan Samson
*/

#include "demogamepanel.h"
#include "src/game/builtindriverfactory.h"

namespace SISDL {

	/**
	 * Public constructor
	 *
	 * @param w The Window
	*/
	DemoGamePanel::DemoGamePanel(Zabbr::SDLWindow* w): GamePanel(w) {
		startGame(new SI::BuiltinDriverFactory());
	}
	
	/**
	 * Destructor;
	*/
	DemoGamePanel::~DemoGamePanel() {
	}
	
	/**
	 * Method called by the window if a key is released.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void DemoGamePanel::keyRelease(SDL_KeyboardEvent evnt) {
		if (evnt.keysym.sym == SDLK_ESCAPE) {
			close();
		} else if (evnt.keysym.sym == SDLK_RETURN) {
			if (!fGame->isPlaying()) {
				close();
			}
		}
	}
}
