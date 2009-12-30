/** \file
 * File for the game panel.
 *
 * @author Nathan Samson
*/

#include "gamepanel.h"
#include "sdlentityfactory.h"

namespace SISDL {

	/**
	 * Public constructor
	 *
	 * @param w The Window
	*/
	GamePanel::GamePanel(Zabbr::SDLWindow* w): Zabbr::VSDLPanel(w),
	                fGame(0), fTimeRemainder(0.0), fClosed(false) {
	}
	
	/**
	 * Destructor;
	*/
	GamePanel::~GamePanel() {
		delete fGame;
		delete fGameVisualizer;
	}
	
	/**
	 * Draws the panel.
	*/
	void GamePanel::draw() {
		if (fClosed && !fIsBackground) {
			openParentPanel();
		}
		
		if (!fTimer.isPaused()) {
			double time = fTimer.reset();
			int ticks = (time + fTimeRemainder) * 1000;
			fTimeRemainder = ((time + fTimeRemainder) * 1000 - ticks) / 1000;
		
			fGame->update(ticks);
		} else {
			fGame->update(0); // Let the entities draw themselves.
		}
		
		if (fIsBackground) {
			fWindow->drawRectangle(0, 0, fWindow->getXResolution(), fWindow->getYResolution(), 0, 0, 0, 0.3);
		}
	}
	
	/**
	 * Method called by the window if a key is pressed.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void GamePanel::keyPress(SDL_KeyboardEvent evnt) {
		fGameVisualizer->keyPress(evnt);
	}
	
	/**
	 * Start a new game.
	*/
	void GamePanel::startGame(SI::IDriverFactory* driverFactory) {
		fGameVisualizer = new SDLGameVisualizer(fWindow);
		fGame = new SI::Game(new SDLEntityFactory(fWindow),
		                     "data/levels/", "firstlevel.silvl",
		                     fGameVisualizer, driverFactory);
		fGame->update(0);
		fTimer.reset();
	}
	
	/**
	 * Close the game.
	*/
	void GamePanel::close() {
		fClosed = true;
	}
	
	/**
	 * Pause the game.
	*/
	void GamePanel::pause() {
		fTimer.pause();
	}
	
	/**
	 * Resume the game.
	*/
	void GamePanel::resume() {
		fTimer.unpause();
	}
}
