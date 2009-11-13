#ifndef _SDLWINDOW_H_
#define _SDLWINDOW_H_

#include <SDL/SDL.h>

namespace sdlframework {



	class SDLWindow {
	public:
		SDLWindow();
		SDLWindow(const SDLWindow&);
		SDLWindow& operator=(const SDLWindow&);
		
		void draw();
		
		void open(int, int, bool);
		void close();

		void drawSurface(SDL_Surface* surface);
	private:
		SDL_Surface *screen;
	};

}

#endif // _SDLWINDOW_
