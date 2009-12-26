#ifndef INC_DEMODRIVER_H
#define INC_DEMODRIVER_H

/** \file
 * File for the demo driver.
 *
 * @author Nathan Samson
*/

#include "game/shipdriver.h"

namespace SI {
	/**
	 * A demo driver. The demo driver will move in random directions for a random time.
	*/
	class DemoDriver: public VShipDriver {
	public:
		virtual void update(int);
	private:
		/**
		 * The time passed since last direction change
		*/
		int fTicksPassedSinceLastChange;
		
		/**
		 * Ticks we are doing this move.
		*/
		int fTicksForMove;
		
		/**
		 * The direction for current move.
		*/
		Vector2 fDirection;
	};
}

#endif // INC_DEMODRIVER_H
