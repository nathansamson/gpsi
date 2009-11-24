#ifndef INC_SHIP_H
#define INC_SHIP_H

#include "misc/vector2.h"
#include "gameentity.h"

namespace SI {
	class Ship: VGameEntity {
	public:
		Ship(int);
		virtual void update(unsigned int);
	private:
		int fStrength;
		Vector2 fSpeed;
	};
}

#endif // INC_SHIP_H
