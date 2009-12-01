#ifndef INC_SHIP_H
#define INC_SHIP_H

#include "misc/vector2.h"
#include "shipdriver.h"
#include "gameentity.h"

namespace SI {
	class VShipDriver;

	/**
	 * The Ship class. A Ship represents a space ship in the space.
	*/
	class Ship: public VGameEntity {
	public:
		Ship(VShipDriver*, Vector2);
		virtual ~Ship();
		
		virtual void update(int);
		friend class VShipDriver;
	private:
		/**
		 * The ship driver.
		*/
		VShipDriver* fShipDriver;
	};
}

#endif // INC_SHIP_H
