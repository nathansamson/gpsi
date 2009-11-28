#ifndef INC_SDLKEYBOARDINPUTDRIVER_H
#define INC_SDLKEYBOARDINPUTDRIVER_H

#include "sdlinputdriver.h"

namespace SISDL {
	class SDLKeyboardInputDriver: public SDLInputDriver {
	public:
		virtual void update(int);
	};
}

#endif // INC_SDLKEYBOARDINPUTDRIVER_H
