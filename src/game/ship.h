#ifndef INC_SHIP_H
#define INC_SHIP_H

#include "misc/vector2.h"
#include "shipdriver.h"
#include "gameentity.h"

namespace SI {
	class VShipDriver;

	class Ship: public VGameEntity {
	public:
		Ship(VShipDriver*);
		virtual ~Ship();
		
		virtual void update(int);
		friend class VShipDriver;
	private:
		VShipDriver* fShipDriver;
	};
}

#endif // INC_SHIP_H
