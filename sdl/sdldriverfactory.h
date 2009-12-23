#ifndef INC_SDLDRIVERFACTORY_H
#define INC_SDLDRIVERFACTORY_H

#include "src/game/builtindriverfactory.h"
#include "sdlkeyboardinputdriver.h"

namespace SISDL {
	/**
	 * The SDL Driver factory.
	*/
	class SDLDriverFactory: public SI::BuiltinDriverFactory {
	public:
		virtual SI::VShipDriver* createUserDriver();
		SDLInputDriver* getUserDriver();
	private:
		/**
		 * The current user driver.
		*/
		SDLInputDriver* fCurUserDriver;
	};
}

#endif // INC_SDLDRIVERFACTORY_H
