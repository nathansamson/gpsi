#ifndef INC_SHIPDRIVER_H
#define INC_SHIPDRIVER_H

#include "misc/vector2.h"
#include "ship.h"

namespace SI {
	class Ship;

	/**
	 * A virtual ship driver.
	*/
	class VShipDriver {
	public:
		VShipDriver();

		/**
		 * Update the ship.
		*/
		virtual void update(int) = 0;
		void bind(Ship*);
	protected:
		void move(Vector2);
	private:
		/**
		 * The ship to driver.
		*/
		Ship* fEntity;
	};
}

#endif // INC_SHIPDRIVER_H
