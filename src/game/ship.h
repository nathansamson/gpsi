#ifndef INC_SHIP_H
#define INC_SHIP_H

#include "misc/vector2.h"
#include "gameentity.h"

namespace SI {
	class Ship: public VGameEntity {
	public:
		Ship(Vector2);
		virtual void update(int);
	private:
		Vector2 fSpeed;
	};
}

#endif // INC_SHIP_H
