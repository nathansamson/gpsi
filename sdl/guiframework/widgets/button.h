#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <string>
#include <list>
#include "SDL.h"

#include "guiframework/widgets/widget.h"
#include "guiframework/events/callbacks.h"
#include "guiframework/events/event.h"

namespace sdlframework {
	class Button : public VWidget {
	public:
		Button(SDLWindow*, std::string label);
		virtual ~Button();

		virtual void draw(int, int);
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);

		// Events
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);

		void connectOnMouseClick(IMouseButtonCallback*);
	private:
		Button();
		std::string fLabel;
		int fWidth;
		int fHeight;
		bool fHover;
		SDL_Rect fBoundingBox;

		int getRealWidth();
		int getRealHeight();

		MouseButtonEvent fMouseClickEvent;
	};
}

#endif // _BUTTON_H_