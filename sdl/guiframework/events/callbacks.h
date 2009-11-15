#include "SDL.h"
#ifndef _EVENTS_H_
#define _EVENTS_H_


namespace sdlframework {
	class IMouseButtonCallback {
	public:
		virtual void call(SDL_MouseButtonEvent) = 0;
	};

}

#endif