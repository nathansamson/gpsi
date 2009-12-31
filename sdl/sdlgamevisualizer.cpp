/** \file
 * File for the SDL game visualizer.
 *
 * @author Nathan Samson
*/

#include "sdl/sdlgamevisualizer.h"

#include <iostream>

namespace SISDL {
	/**
	 * Constructor.
	 *
	 * @param window The SDLWindow.
	*/
	SDLGameVisualizer::SDLGameVisualizer(Zabbr::SDLWindow* window):
	    fWindow(window), fInNonGamePhase(false) {
	    SDL_Color white = {255, 255, 255};
	    fStatusLabel = new Zabbr::Label(fWindow, "", white, Zabbr::FONTSIZE_BIG);
	}
	
	SDLGameVisualizer::~SDLGameVisualizer() {
		delete fStatusLabel;
	}
	
	/**
	 * Draw the game visualization.
	*/
	void SDLGameVisualizer::draw() {
		if (fInNonGamePhase) {
			fStatusLabel->draw((fWindow->getXResolution() - fStatusLabel->getWidth()) / 2,
			                   (fWindow->getYResolution() - fStatusLabel->getHeight()) / 2);
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
		fStatusLabel->setLabel("You loose!");
	}
	
	/**
	 * Let the visualizer know that the user has won.
	*/
	void SDLGameVisualizer::userWins() {
		fInNonGamePhase = true;
		fStatusLabel->setLabel("You win!");
	}
	
	/**
	 * Let the visualizer know that the level changed.
	 *
	 * @param name The name of the level.
	*/
	void SDLGameVisualizer::levelChange(std::string name) {
		fInNonGamePhase = true;
		fStatusLabel->setLabel(name);
	}
	
	/**
	 * A key press function.
	 *
	 * @param evnt The SDL_KeyboardEvent the keyboard event.
	*/
	void SDLGameVisualizer::keyPress(SDL_KeyboardEvent evnt) {
		fInNonGamePhase = false;
	}
}
