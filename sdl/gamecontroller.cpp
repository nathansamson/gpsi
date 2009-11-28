#include "gamecontroller.h"
#include "sdlentityfactory.h"
#include "sdlkeyboardinputdriver.h"

namespace SISDL {
	GameController::GameController(Zabbr::SDLWindow* w): Zabbr::VSDLController(w), fGame(0), fTimeRemainder(0.0) {
		fInputDriver = new SDLKeyboardInputDriver();
		fGame = new SI::Game(fInputDriver, new SDLEntityFactory(w));
	}
	
	GameController::~GameController() {
		delete fGame;
	}
	
	void GameController::draw() {
		double time = fTimer.reset();
		int ticks = (time + fTimeRemainder) * 1000;
		fTimeRemainder = (time + fTimeRemainder) * 1000 - ticks;
		
		fGame->update(ticks);
	}
}
