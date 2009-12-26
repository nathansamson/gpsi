#ifndef INC_SYNCHRONOUSDRIVER_H
#define INC_SYNCHRONOUSDRIVER_H

/** \file
 * File for the synchronous driver.
 *
 * @author Nathan Samson
*/

#include "game/shipdriver.h"

namespace SI {
	/**
	 * A synchronous driver. The synchronous driver will bounce after some distance moved in a direction.
	*/
	class SynchronousDriver: public VShipDriver {
	public:
		SynchronousDriver(double);
		
		virtual void update(int);
	private:
		/**
		 * The minimal distance to the border of the game field.
		*/
		double fXMargin;
		
		/**
		 * The offset from the start.
		*/
		Vector2 fMoved;
		
		/**
		 * The direction of the ship.
		 *
		 * Positive when going right, negative when going left.
		*/
		int fDir;
	};
}

#endif // INC_SYNCHRONOUSDRIVER_H
