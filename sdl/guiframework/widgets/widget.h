#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SDL/SDL.h>

#include "guiframework/sdlwindow.h"

namespace sdlframework {

	class VWidget {
	public:
		VWidget(SDLWindow*);

		virtual void draw(int, int) = 0;
		virtual int getWidth() = 0;
		virtual void setWidth(int) = 0;
		virtual int getHeight() = 0;
		virtual void setHeight(int) = 0;
		void setFill(bool);

		// Events
		virtual void mouseMotion(SDL_MouseMotionEvent);
	protected:
		SDLWindow* fWindow;
		bool fFill;
	private:
		VWidget();
	};
}

#endif //_WIDGET_H_