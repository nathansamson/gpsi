#include "SDL.h"
#ifndef INC_EVENTS_H
#define INC_EVENTS_H


namespace sdlframework {
	class IMouseButtonCallback {
	public:
		virtual void call(SDL_MouseButtonEvent) = 0;
	};

}

#endif // INC_EVENTS_H