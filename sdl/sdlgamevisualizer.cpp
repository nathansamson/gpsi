#include "sdl/sdlgamevisualizer.h"

#include <iostream>

namespace SISDL {
	SDLGameVisualizer::SDLGameVisualizer(Zabbr::SDLWindow* window):
	    fWindow(window), fInNonGamePhase(false), fStatusText(0) {
	}
	
	void SDLGameVisualizer::draw() {
		if (fInNonGamePhase) {
			fWindow->drawSurface(fStatusText, 0, 0);
		}
	}
	
	bool SDLGameVisualizer::inNonGamePhase() {
		return fInNonGamePhase;
	}
	
	void SDLGameVisualizer::userDies() {
		fInNonGamePhase = true;
		showString("You loose!");
	}
	
	void SDLGameVisualizer::userWins() {
		fInNonGamePhase = true;
		showString("You win!");
	}
	
	void SDLGameVisualizer::levelChange(std::string name) {
		fInNonGamePhase = true;
		showString(name);
	}
	
	void SDLGameVisualizer::showString(std::string str) {
		Zabbr::FontResource* font = Zabbr::ResourceManager::manager().font("DejaVuSans-Bold.ttf", 30);
		SDL_Color c = {255, 255, 255};
		fStatusText = Zabbr::ResourceManager::manager().string(str, font, c);
		Zabbr::ResourceManager::manager().free(font);
	}
	
	void SDLGameVisualizer::keyPress(SDL_KeyboardEvent evnt) {
		if (!fInNonGamePhase) return;
		if (evnt.keysym.sym == SDLK_RETURN || evnt.keysym.sym == SDLK_SPACE) {
			fInNonGamePhase = false;
			Zabbr::ResourceManager::manager().free(fStatusText);
			fStatusText = 0;
		}
	}
}
