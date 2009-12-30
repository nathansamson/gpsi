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
	 * @param xMargin The maximal movement on the x-axis
	*/
	SynchronousDriver::SynchronousDriver(double xMargin): fXMargin(xMargin), fMoved(0.0, 0.0), fDir(1) {
		std::srand(time(0));
	}
	
	/**
	 * A Synchronous driver.
	 *
	 * @param xMargin The maximal movement on the x-axis
	 * @param offset The movement already done.
	*/
	SynchronousDriver::SynchronousDriver(double xMargin, double offset): fXMargin(xMargin), fMoved(offset, 0.0), fDir(1) {
		std::srand(time(0));
	}
	
	/**
	 * Update the state of the ship.
	 *
	 * @param ticks Ticks passed since last update.
	*/
	void SynchronousDriver::update(int ticks) {
		if (ticks == 0) return;
	
		Vector2 step = Vector2(fDir*1.0*ticks, -1.0*ticks);
		Vector2 requested = step;
		move(step, ticks);
		fMoved += step;
		if (fMoved.getX() >= fXMargin || fMoved.getX() <= -fXMargin) {
			if (fMoved.getX() > 0) {
				fDir = -1;
			} else {
				fDir = 1;
			}
		}
		
		if (std::rand() % (25000 / ticks) == 0) {
			fire();
		} 
	}
}
