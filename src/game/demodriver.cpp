/** \file
 * File for the demo driver.
 *
 * @author Nathan Samson
*/

#include <cmath>
#include <cstdlib>

#include "game/demodriver.h"

namespace SI {
	/**
	 * Update the state of the ship.
	 *
	 * @param ticks Ticks passed since last update.
	*/
	void DemoDriver::update(int ticks) {
		if (ticks == 0) return;
	
		Vector2 step = ticks * fDirection;
		move(step, ticks);
		if ((int)(step.getX() * 1000) == 0) {
			fTicksPassedSinceLastChange = fTicksForMove;
		}
		
		fTicksPassedSinceLastChange += ticks;
		if (fTicksPassedSinceLastChange >= fTicksForMove) {
			fTicksForMove = rand() % 1000 + 500;
			fDirection = Vector2((rand() % 3 - 1) * 1.0, (rand() % 3 - 1) * 1.0);
			fTicksPassedSinceLastChange = 0;
		}
		if (rand() % 1000) {
			fire();
		}
	}
}
