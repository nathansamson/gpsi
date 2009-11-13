#include <SDL/SDL.h>
#include <iostream>

#include "sdlwindow.h"

namespace sdlframework {

SDLWindow::SDLWindow() {
	
}

SDLWindow::SDLWindow(const SDLWindow&) {
	
}

SDLWindow& SDLWindow::operator=(const SDLWindow&) {
	
}

void SDLWindow::open(int xres, int yres, bool fs) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << SDL_GetError() << std::endl;;
		//printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return;
	}
 
	atexit(SDL_Quit);
 
	screen = SDL_SetVideoMode(xres, yres, 0, SDL_DOUBLEBUF);
	if (screen == NULL) {
		std::cout << SDL_GetError() << std::endl;;
		//printf("Unable to set video mode: %s\n", SDL_GetError());
		return;
	}
}

void SDLWindow::close() {
	SDL_FreeSurface(screen);
}

void SDLWindow::draw() {
	SDL_Flip(screen);
}

void SDLWindow::drawSurface(SDL_Surface* s) {
	SDL_Rect src, dest;
	
	src.x = 0;
	src.y = 0;
	src.w = 100;
	src.h = 100;
	
	dest.x = 20;
	dest.y = 20;
	dest.w = 200;
	dest.h = 200;
	
	SDL_BlitSurface(s, &src, screen, &dest);
}

}
