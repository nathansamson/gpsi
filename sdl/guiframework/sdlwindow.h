#ifndef _SDLWINDOW_H_
#define _SDLWINDOW_H_

#include <SDL/SDL.h>

#include "guiframework/resources/imageresource.h"

namespace sdlframework {



	class SDLWindow {
	public:
		SDLWindow();
		SDLWindow(const SDLWindow&);
		SDLWindow& operator=(const SDLWindow&);
		
		void draw();
		
		void open(int, int, bool);
		void close();

		void drawImage(ImageResource*, int, int);
		void drawImage(ImageResource*, int, int, double);
	private:
		SDL_Surface *screen;
	};

}

#endif // _SDLWINDOW_
