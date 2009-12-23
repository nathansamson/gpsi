#include "sdl/sdlgamevisualizer.h"

#include <iostream>

namespace SISDL {
	/**
	 * Constructor.
	 *
	 * @param window The SDLWindow.
	*/
	SDLGameVisualizer::SDLGameVisualizer(Zabbr::SDLWindow* window):
	    fWindow(window), fInNonGamePhase(false), fStatusText(0) {
	}
	
	/**
	 * Draw the game visualization.
	*/
	void SDLGameVisualizer::draw() {
		if (fInNonGamePhase) {
			fWindow->drawSurface(fStatusText, 0, 0);
		}
	}
	
	/**
	 * Checks if we are in a non game state (like pause, level change).
	 *
	 * @return True if we are in a non game phase
	*/
	bool SDLGameVisualizer::inNonGamePhase() {
		return fInNonGamePhase;
	}
	
	/**
	 * Let the visualizer know that the user died.
	*/
	void SDLGameVisualizer::userDies() {
		fInNonGamePhase = true;
		showString("You loose!");
	}
	
	/**
	 * Let the visualizer know that the user has won.
	*/
	void SDLGameVisualizer::userWins() {
		fInNonGamePhase = true;
		showString("You win!");
	}
	
	/**
	 * Let the visualizer know that the level changed.
	 *
	 * @param name The name of the level.
	*/
	void SDLGameVisualizer::levelChange(std::string name) {
		fInNonGamePhase = true;
		showString(name);
	}
	
	/**
	 * Show a string in the center of the screen.
	 *
	 * @param str The string.
	*/
	void SDLGameVisualizer::showString(std::string str) {
		Zabbr::FontResource* font = Zabbr::ResourceManager::manager().font("DejaVuSans-Bold.ttf", 30);
		SDL_Color c = {255, 255, 255};
		fStatusText = Zabbr::ResourceManager::manager().string(str, font, c);
		Zabbr::ResourceManager::manager().free(font);
	}
	
	/**
	 * A key press function.
	 *
	 * @param evnt The SDL_KeyboardEvent the keyboard event.
	*/
	void SDLGameVisualizer::keyPress(SDL_KeyboardEvent evnt) {
		if (!fInNonGamePhase) return;
		if (evnt.keysym.sym == SDLK_RETURN || evnt.keysym.sym == SDLK_SPACE) {
			fInNonGamePhase = false;
			Zabbr::ResourceManager::manager().free(fStatusText);
			fStatusText = 0;
		}
	}
}
