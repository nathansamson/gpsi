#ifndef INC_MENUCONTROLLER_H
#define INC_MENUCONTROLLER_H

#include <list>
#include "SDL.h"

#include "guiframework/controller/sdlcontroller.h"
#include "guiframework/widgets/widget.h"

namespace sdlframework {

	class MenuController : public VSDLController {
	public:
		MenuController(SDLWindow*);
		MenuController(const MenuController&);
		virtual ~MenuController();

		void addWidget(VWidget*);

		virtual void draw();
		virtual void keyDown(SDL_KeyboardEvent);
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void quit();
	private:
		std::list<VWidget*> fWidgets;
	};

}

#endif // _MENUCONTROLLER_H_
