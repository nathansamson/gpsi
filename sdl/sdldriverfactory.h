#ifndef INC_SDLDRIVERFACTORY_H
#define INC_SDLDRIVERFACTORY_H

#include "src/game/builtindriverfactory.h"
#include "sdlkeyboardinputdriver.h"

namespace SISDL {
	class SDLDriverFactory: public SI::BuiltinDriverFactory {
	public:
		virtual SI::VShipDriver* createUserDriver();
		SDLInputDriver* getUserDriver();
	private:
		SDLInputDriver* fCurUserDriver;
	};
}

#endif // INC_SDLDRIVERFACTORY_H
