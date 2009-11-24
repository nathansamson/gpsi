#ifndef INC_SHIP_H
#define INC_SHIP_H

#include "misc/vector2.h"
#include "shipcontroller.h"
#include "gameentity.h"

namespace SI {
	class Ship: public VGameEntity {
	public:
		Ship(VShipController*);
		virtual ~Ship();
		
		virtual void update(int);
	private:
		VShipController* fMoveController;
	};
}

#endif // INC_SHIP_H
