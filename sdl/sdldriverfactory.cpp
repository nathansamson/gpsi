/** \file
 * File for the sdl driver factory.
 *
 * @author Nathan Samson
*/

#include "sdldriverfactory.h"

namespace SISDL {
	/**
	 * Creates a user driver.
	 *
	 * @return A user driver.
	*/
	SI::VShipDriver* SDLDriverFactory::createUserDriver() {
		fCurUserDriver = new SDLKeyboardInputDriver();
		return fCurUserDriver;
	}
	
	/**
	 * Get the current user driver.
	 *
	 * @return the current user driver.
	*/
	SDLInputDriver* SDLDriverFactory::getUserDriver() {
		return fCurUserDriver;
	}
}
