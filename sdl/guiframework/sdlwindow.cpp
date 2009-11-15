#include <iostream>

#include "SDL.h"

#include "guiframework/sdlwindow.h"
#include "guiframework/controller/sdlcontroller.h"
#include "guiframework/resources/imageresource.h"

namespace sdlframework {

SDLInitializationException::SDLInitializationException(std::string s) : fError(s) {
}

std::string SDLInitializationException::getError() {
	return fError;
}

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
		throw SDLInitializationException(SDL_GetError());
	}

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(xres, yres, 0, SDL_DOUBLEBUF);
	if (screen == NULL) {
		throw SDLInitializationException(SDL_GetError());
	}
}

void SDLWindow::close() {
	if (screen)
		SDL_FreeSurface(screen);
}

void SDLWindow::run(VSDLController* controller) {
	fController = controller;
	SDL_Event event;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					fController->keyDown(event.key);
					break;
				case SDL_MOUSEMOTION:
					fController->mouseMotion(event.motion);
					break;
				case SDL_QUIT:
					fController->quit();
					break;
			}
		}
		
		if (fController && screen) { // It is possible that we already have closed our controller.
			drawRectangle(0, 0, screen->w, screen->h, 0, 0, 0);
			fController->draw();
			draw();
			SDL_Delay(1);
		} else {
			screen = NULL;
			running = false;
		}
	}
}

void SDLWindow::draw() {
	SDL_Flip(screen);
}

void SDLWindow::closeController(VSDLController* next) {
	delete fController;
	fController = next;
	if (next == NULL) {
		SDL_Quit();
	}
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

void SDLWindow::drawRectangle(int x, int y, int w, int h, int r, int g, int b) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	

	SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, r, g, b));
}

}
