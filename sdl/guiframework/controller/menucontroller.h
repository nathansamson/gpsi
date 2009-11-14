#ifndef _MENUCONTROLLER_H_
#define _MENUCONTROLLER_H_

#include <SDL/SDL.h>

#include "guiframework/controller/sdlcontroller.h"

namespace sdlframework {

	class MenuController : public VSDLController {
	public:
		MenuController(SDLWindow*);
		MenuController(const MenuController&);
		virtual ~MenuController();
		
		virtual void draw();
		virtual void keyDown(SDL_KeyboardEvent);
		virtual void quit();
	};

}

#endif // _MENUCONTROLLER_H_
