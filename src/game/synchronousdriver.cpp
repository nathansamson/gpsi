/** \file
 * File for the synchronous driver.
 *
 * @author Nathan Samson
*/

#include <cmath>
#include <cstdlib>

#include "game/synchronousdriver.h"

namespace SI {
	/**
	 * A Synchronous driver.
	 *
	 * @param xMargin The minimal distance to the border.
	*/
	SynchronousDriver::SynchronousDriver(double xMargin): fXMargin(xMargin), fMoved(0.0, 0.0), fDir(1) {
		std::srand(time(0));
	}
	
	/**
	 * Update the state of the ship.
	 *
	 * @param ticks Ticks passed since last update.
	*/
	void SynchronousDriver::update(int ticks) {
		if (ticks == 0) return;
	
		Vector2 step = Vector2(fDir*0.0002*ticks, -0.0001*ticks);
		if (std::fabs((fMoved+step).getX()) >= fXMargin-1E-8) {
			if (fDir == 1) {
				step -= 2*Vector2((fMoved+step).getX()-fXMargin, 0.0);
			} else {
				step -= 2*Vector2((fMoved+step).getX()+fXMargin, 0.0);
			}
			fDir *= -1;
		}
		move(step, ticks);
		fMoved += step;
		
		if (std::rand() % (25000 / ticks) == 0) {
			fire();
		} 
	}
}
