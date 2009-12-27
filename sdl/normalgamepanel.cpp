/** \file
 * File for the SDL game panel.
 *
 * @author Nathan Samson
*/

#include <sstream>

#include "zabbr/widgets/button.h"
#include "zabbr/events/callbacks.h"
#include "zabbr/resources/resourcemanager.h"

#include "normalgamepanel.h"
#include "highscorepanel.h"
#include "sdlkeyboardinputdriver.h"
#include "sdldriverfactory.h"

namespace SISDL {
	
	/**
	 * Public constructor
	 *
	 * @param w The Window
	*/
	NormalGamePanel::NormalGamePanel(Zabbr::SDLWindow* w): GamePanel(w) {
		fDriverFactory = new SDLDriverFactory();
		startGame(fDriverFactory);
		connectRequestQuit(new Zabbr::ClassCallback0<NormalGamePanel>(this, &NormalGamePanel::onRequestQuitGame));
		
		SDL_Color white = {255, 255, 255};
		fScoreLabel = new Zabbr::Label(fWindow, "", white, Zabbr::FONTSIZE_SMALL);
	}
	
	NormalGamePanel::~NormalGamePanel() {
		delete fScoreLabel;
	}
	
	/**
	 * Draws the panel.
	*/
	void NormalGamePanel::draw() {
		GamePanel::draw();
		
		if (!fGameVisualizer->inNonGamePhase()) {
			std::stringstream ssScoreText;
			ssScoreText << fGame->getUserScore();
			std::string scoreText;
			ssScoreText >> scoreText;
			fScoreLabel->setLabel(scoreText);
			fScoreLabel->draw(10, 10);
		}
	}
	
	/**
	 * Method called by the window if a key is pressed.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void NormalGamePanel::keyPress(SDL_KeyboardEvent evnt) {
		GamePanel::keyPress(evnt);
		fInputDriver = fDriverFactory->getUserDriver();
		if (!fGame->isUserDead()) fInputDriver->keyDown(evnt);
	}
	
	/**
	 * Method called by the window if a key is released.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void NormalGamePanel::keyRelease(SDL_KeyboardEvent evnt) {
		fInputDriver = fDriverFactory->getUserDriver();
		if (!fGame->isUserDead()) fInputDriver->keyRelease(evnt);
		if (evnt.keysym.sym == SDLK_ESCAPE) {
			requestQuit();
		} else if (evnt.keysym.sym == SDLK_RETURN) {
			if (!fGame->isPlaying()) {
				// TODO: Show a menu to choose what to do
				
				// Play new game
				// Go to main menu
				// Quit
				close();
				openPanel(new HighscorePanel(fWindow, fGame->getUserScore()));
			}
		}
	}
	
	/**
	 * Method callback that is called when the panel is requested to quit.
	*/
	void NormalGamePanel::onRequestQuitGame() {
		pause();
		fQuitConfirmation = new Zabbr::MenuPanel(fWindow, "Game Paused");
		Zabbr::Button* b = new Zabbr::Button(fWindow, "Resume game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<NormalGamePanel, SDL_MouseButtonEvent>(this, &NormalGamePanel::onResumeGame));
		fQuitConfirmation->addButton(b);

		b = new Zabbr::Button(fWindow, "Quit Game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<NormalGamePanel, SDL_MouseButtonEvent>(this, &NormalGamePanel::onQuitGame));
		fQuitConfirmation->addButton(b);
		
		b = new Zabbr::Button(fWindow, "Close game");
		b->connectOnMouseClick(new Zabbr::ClassCallback1<NormalGamePanel, SDL_MouseButtonEvent>(this, &NormalGamePanel::onCloseGame));
		fQuitConfirmation->addButton(b);
		fQuitConfirmation->connectOnKeyRelease(new Zabbr::ClassCallback2<NormalGamePanel, Zabbr::VSDLPanel*, SDL_KeyboardEvent>(this, &NormalGamePanel::onKeyReleaseQuitConfirmation));
		fQuitConfirmation->connectRequestQuit(new Zabbr::ClassCallback0<NormalGamePanel>(this, &NormalGamePanel::onQuitConfirmationQuit));

		openPanel(fQuitConfirmation);
	}
	
	/**
	 * Resume game callback.
	*/
	void NormalGamePanel::onResumeGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->openParentPanel();
		resume();
	}
	
	/**
	 * Quit game callback.
	*/
	void NormalGamePanel::onQuitGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->openParentPanel();
		close();
		openPanel(new HighscorePanel(fWindow, fGame->getUserScore()));
	}
	
	/**
	 * Close game callback.
	*/
	void NormalGamePanel::onCloseGame(SDL_MouseButtonEvent e) {
		fQuitConfirmation->quit();
	}
	
	/**
	 * Key release callback.
	 *
	 * @param panel The panel
	 * @parem event The event
	*/
	void NormalGamePanel::onKeyReleaseQuitConfirmation(Zabbr::VSDLPanel* panel, SDL_KeyboardEvent event) {
		if (event.keysym.sym == SDLK_ESCAPE) {
			fQuitConfirmation->openParentPanel();
			resume();
		}
	}
	
	/**
	 * Quit request callback for the quit confirmation.
	*/
	void NormalGamePanel::onQuitConfirmationQuit() {
		fQuitConfirmation->openParentPanel();
		close();
		openPanel(new HighscorePanel(fWindow, fGame->getUserScore()));
	}
}
