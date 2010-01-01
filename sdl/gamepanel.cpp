/** \file
 * File for the game panel.
 *
 * @author Nathan Samson
*/

#include <exception>

#include "resources/resourcemanager.h"
#include "gamepanel.h"
#include "sdlentityfactory.h"

namespace SISDL {

	/**
	 * Public constructor
	 *
	 * @param w The Window
	*/
	GamePanel::GamePanel(Zabbr::SDLWindow* w): Zabbr::VSDLPanel(w),
	                fGame(0), fTimeRemainder(0.0), fClosed(false), fErrorLabel(0) {
	}
	
	/**
	 * Destructor;
	*/
	GamePanel::~GamePanel() {
		delete fGame;
		delete fGameVisualizer;
		if (fErrorLabel) delete fErrorLabel;
	}
	
	/**
	 * Draws the panel.
	*/
	void GamePanel::draw() {
		if (fClosed && !fIsBackground) {
			openParentPanel();
			return;
		}
		
		if (fErrorLabel) {
			fErrorLabel->draw(fWindow->getXResolution() / 2 - fErrorLabel->getWidth() / 2,
			                  fWindow->getYResolution() / 2 - fErrorLabel->getHeight() / 2);
			return;
		}
		
		if (!fTimer.isPaused()) {
			double time = fTimer.reset();
			int ticks = (time + fTimeRemainder) * 1000;
			fTimeRemainder = ((time + fTimeRemainder) * 1000 - ticks) / 1000;
		
			try {
				fGame->update(ticks);
			} catch (std::exception& e) {
				error(e.what());
				return;
			}
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
		if (fErrorLabel) {
			close();
		}
	}
	
	/**
	 * Start a new game.
	*/
	void GamePanel::startGame(SI::IDriverFactory* driverFactory) {
		fGameVisualizer = new SDLGameVisualizer(fWindow);
		try {
			fGame = new SI::Game(new SDLEntityFactory(fWindow),
			                     Zabbr::ResourceManager::fgDataPath+"/levels/", "firstlevel.silvl",
			                     fGameVisualizer, driverFactory);
		fGame->update(0);
		} catch (std::exception& e) {
			error(e.what());
			return;
		}
		fTimer.reset();
	}
	
	/**
	 * Close the game.
	*/
	void GamePanel::close() {
		fClosed = true;
	}
	
	/**
	 * Show an error.
	*/
	void GamePanel::error(std::string error) {
		SDL_Color white = {255, 255, 255};
		fErrorLabel = new Zabbr::Label(fWindow, error, white);
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
