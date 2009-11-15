#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <string>
#include "SDL.h"

#include "guiframework/widgets/widget.h"

namespace sdlframework {
	class Button : public VWidget {
	public:
		Button(SDLWindow*, std::string label);

		virtual void draw(int, int);
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);

		// Events
		virtual void mouseMotion(SDL_MouseMotionEvent);
	private:
		Button();
		std::string fLabel;
		int fWidth;
		int fHeight;
		bool fHover;
		SDL_Rect fBoundingBox;

		int getRealWidth();
		int getRealHeight();
	};
}

#endif // _BUTTON_H_