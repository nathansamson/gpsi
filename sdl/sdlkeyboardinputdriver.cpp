#include <cmath>
#include "sdlkeyboardinputdriver.h"

namespace SISDL {

	SDLKeyboardInputDriver::SDLKeyboardInputDriver(): fLeft(false), fRight(false), fFire(false), fSpeed(SI::Vector2(0, 0)) {
	}

	/**
	 * Update the driver.
	*/
	void SDLKeyboardInputDriver::update(int ticks) {
		const double max = 0.01;
		
		if ((fLeft && fRight) || !(fLeft || fRight)) {
			fSpeed *= 0;
		} else if (fLeft) {
			fSpeed -= SI::Vector2(max/500, 0.0);
		} else if (fRight) {
			fSpeed += SI::Vector2(max/500, 0.0); 
		}
		
		if (std::fabs(fSpeed.getX()) > max) {
			if (fLeft) {
				fSpeed.setX(-max);
			} else {
				fSpeed.setX(max);
			}
		}
		
		move(fSpeed * ticks);
		if (fFire) {
			fire();
		}
	}
	
	/**
	 * Callback for keypress.
	 *
	 * @param evnt The SDL_KeyboardEvent.
	*/
	void SDLKeyboardInputDriver::keyDown(SDL_KeyboardEvent evnt) {
		if (evnt.keysym.sym == SDLK_LEFT) {
			fLeft = true;
		} else if (evnt.keysym.sym == SDLK_RIGHT) {
			fRight = true;
		} else if (evnt.keysym.sym == SDLK_SPACE) {
			fFire = true;
		}
	}
	
	/**
	 * Callback for keyrelease.
	 *
	 * @param evnt The SDL_KeyboardEvent.
	*/
	void SDLKeyboardInputDriver::keyRelease(SDL_KeyboardEvent evnt) {
		if (evnt.keysym.sym == SDLK_LEFT) {
			fLeft = false;
		} else if (evnt.keysym.sym == SDLK_RIGHT) {
			fRight = false;
		} else if (evnt.keysym.sym == SDLK_SPACE) {
			fFire = false;
		}
	}
}
