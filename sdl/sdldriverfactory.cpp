#include "sdldriverfactory.h"


namespace SISDL {
	SI::VShipDriver* SDLDriverFactory::createUserDriver() {
		fCurUserDriver = new SDLKeyboardInputDriver();
		return fCurUserDriver;
	}
	
	SDLInputDriver* SDLDriverFactory::getUserDriver() {
		return fCurUserDriver;
	}
}
