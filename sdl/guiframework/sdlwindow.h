#ifndef _SDLWINDOW_H_
#define _SDLWINDOW_H_

#include <string>
#include "SDL.h"

#include "guiframework/resources/imageresource.h"

namespace sdlframework {

	class VSDLController;

	class SDLInitializationException {
	public:
		SDLInitializationException(std::string);
		std::string getError();
	private:
		std::string fError;
	};

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
	protected:
		VSDLController* fController;
	private:
		VSDLController* fOldController;
		SDL_Surface* screen;
		bool fRunning;
	};

}

#endif // _SDLWINDOW_
