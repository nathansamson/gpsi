#ifndef INC_SDLKEYBOARDINPUTDRIVER_H
#define INC_SDLKEYBOARDINPUTDRIVER_H

#include "sdlinputdriver.h"

namespace SISDL {
	class SDLKeyboardInputDriver: public SDLInputDriver {
	public:
		virtual void update(int);
		virtual void keyDown(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
	private:
		bool fLeft;
		bool fRight;
		
		SI::Vector2 fSpeed;
	};
}

#endif // INC_SDLKEYBOARDINPUTDRIVER_H
