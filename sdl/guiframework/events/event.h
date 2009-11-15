#ifndef _EVENT_H_
#define _EVENT_H_

#include <list>
#include "SDL.h"

#include "guiframework/events/callbacks.h"

namespace sdlframework {
	class MouseButtonEvent {
	public:
		~MouseButtonEvent();

		void connect(IMouseButtonCallback*);
		void fire(SDL_MouseButtonEvent);
	private:
		std::list<IMouseButtonCallback*> fCallbacks;
	};
}

#endif