#include "zabbr/controller/sdlcontroller.h"
#include "zabbr/misc/stopwatch.h"
#include "src/game/game.h"

#include "sdlinputdriver.h"

namespace SISDL {
	
	class GameController: public Zabbr::VSDLController {
	public:
		GameController(Zabbr::SDLWindow*);
		~GameController();
	
		virtual void draw();
	private:
		SI::Game* fGame;
		SDLInputDriver* fInputDriver;
		Zabbr::Stopwatch fTimer;
		double fTimeRemainder;
	};
}
