#ifndef SDL_INPUTDRIVER_H
#define SDL_INPUTDRIVER_H

/** \file
 * File for the SDL input driver.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

#include "src/game/shipdriver.h"

namespace SISDL {
	/**
	 * Virtual base class for SDL Input drivers.
	*/
	class SDLInputDriver: public SI::VShipDriver {
	public:
		virtual void keyDown(SDL_KeyboardEvent) = 0;
		virtual void keyRelease(SDL_KeyboardEvent) = 0;
	};
}

#endif // SDL_INPUTDRIVER_H
