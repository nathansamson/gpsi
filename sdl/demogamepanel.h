#ifndef INC_DEMOGAMEPANEL_H
#define INC_DEMOGAMEPANEL_H

/** \file
 * File for the SDL game panel.
 *
 * @author Nathan Samson
*/

#include "gamepanel.h"

namespace SISDL {
	
	/**
	 * The demo game panel.
	*/
	class DemoGamePanel: public GamePanel {
	public:
		DemoGamePanel(Zabbr::SDLWindow*);
		virtual ~DemoGamePanel();
	
		virtual void keyRelease(SDL_KeyboardEvent);
	};
}

#endif // INC_GAMEPANEL_H
