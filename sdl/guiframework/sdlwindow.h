#ifndef _SDLWINDOW_H_
#define _SDLWINDOW_H_

#include <SDL/SDL.h>

#include "guiframework/resources/imageresource.h"

namespace sdlframework {

	class VSDLController;

	class SDLWindow {
	public:
		SDLWindow();
		SDLWindow(const SDLWindow&);
		SDLWindow& operator=(const SDLWindow&);
		
		void draw();
		
		void open(int, int, bool);
		void close();
		
	    void run(VSDLController*);

		/***** API for controllers ******/
		
		void closeController(VSDLController*);
		
		void drawImage(ImageResource*, int, int);
		void drawImage(ImageResource*, int, int, double);
		void drawRectangle(int, int, int, int, int, int, int);
	private:
		SDL_Surface* screen;
		VSDLController* fController;
	};

}

#endif // _SDLWINDOW_
