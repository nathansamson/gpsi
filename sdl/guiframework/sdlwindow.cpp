#include <SDL/SDL.h>
#include <iostream>

#include "guiframework/sdlwindow.h"
#include "guiframework/resources/imageresource.h"

namespace sdlframework {

SDLWindow::SDLWindow() {
	
}

SDLWindow::SDLWindow(const SDLWindow&) {
	
}

SDLWindow& SDLWindow::operator=(const SDLWindow& rhs) {
	screen = rhs.screen;
	return *this;
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

void SDLWindow::drawImage(ImageResource* img, int x, int y) {
	drawImage(img, x, y, 1.0);
}

void SDLWindow::drawImage(ImageResource* img, int x, int y, double scale) {
	SDL_Rect src, dest;
	
	src.x = 0;
	src.y = 0;
	src.w = img->getWidth();
	src.h = img->getHeight();
	
	dest.x = x;
	dest.y = y;
	dest.w = img->getWidth() * scale;
	dest.h = img->getHeight() * scale;
	
	SDL_BlitSurface(img->getSurface(), &src, screen, &dest);
}

}
