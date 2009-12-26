#ifndef INC_SDLKEYBOARDINPUTDRIVER_H
#define INC_SDLKEYBOARDINPUTDRIVER_H

/** \file
 * File for the SDL keyboard input driver.
 *
 * @author Nathan Samson
*/

#include "sdlinputdriver.h"

namespace SISDL {
	/**
	 * The Keyboard driver.
	*/
	class SDLKeyboardInputDriver: public SDLInputDriver {
	public:
		SDLKeyboardInputDriver();

		virtual void update(int);
		virtual void keyDown(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
	private:
		/**
		 * True if key associated with left is pressed.
		*/
		bool fLeft;
		/**
		 * True if the key associated with right is pressed.
		*/
		bool fRight;
		/**
		 * True if the user requested a fire.
		*/
		bool fFire;
		
		/**
		 * The current speed per tick of the ship.
		*/
		SI::Vector2 fSpeed;
	};
}

#endif // INC_SDLKEYBOARDINPUTDRIVER_H
