#include "sdlkeyboardinputdriver.h"

namespace SISDL {

	void SDLKeyboardInputDriver::update(int ticks) {
		move(SI::Vector2(0.000001*ticks, 0.0));
	}
}
