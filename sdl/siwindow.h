#ifndef _SIWINDOW_H_
#define _SIWINDOW_H_

#include "guiframework/sdlwindow.h"

namespace sisdl {
	using namespace sdlframework;


	class SIWindow : public  SDLWindow {
	public:
		void run();
	};

}

#endif // _SIWINDOW_H_
