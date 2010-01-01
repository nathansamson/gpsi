#ifndef INC_GAMEPANEL_H
#define INC_GAMEPANEL_H

/** \file
 * File for the SDL game panel.
 *
 * @author Nathan Samson
*/

#include "zabbr/panels/sdlpanel.h"
#include "zabbr/misc/stopwatch.h"
#include "src/game/game.h"
#include "zabbr/resources/resourcemanager.h"
#include "zabbr/widgets/label.h"

#include "sdlinputdriver.h"
#include "sdldriverfactory.h"
#include "sdlgamevisualizer.h"

namespace SISDL {
	
	/**
	 * The game panel.
	*/
	class GamePanel: public Zabbr::VSDLPanel {
	public:
		GamePanel(Zabbr::SDLWindow*);
		virtual ~GamePanel();
	
		virtual void draw();
		virtual void keyPress(SDL_KeyboardEvent);
	protected:
		void startGame(SI::IDriverFactory*);
		
		void close();
		void pause();
		void resume();
		void error(std::string);
		
		/**
		 * The game
		*/
		SI::Game* fGame;
	protected:
		/**
		 * The game visualizer.
		*/
		SDLGameVisualizer* fGameVisualizer;
	private:		
		/**
		 * The timer.
		*/
		Zabbr::Stopwatch fTimer;
		
		/**
		 * The remaining time of last frame.
		*/
		double fTimeRemainder;
		
		/**
		 * Flag to see if we should close.
		*/
		bool fClosed;
		
		/**
		 * Error label
		*/
		Zabbr::Label* fErrorLabel;
	};
}

#endif // INC_GAMEPANEL_H
