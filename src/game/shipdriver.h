#ifndef INC_SHIPDRIVER_H
#define INC_SHIPDRIVER_H

#include "misc/vector2.h"
#include "ship.h"

namespace SI {
	class Ship;

	class VShipDriver {
	public:
		VShipDriver();

		virtual void update(int) = 0;
		void bind(Ship*);
	protected:
		void move(Vector2);
	private:
		Ship* fEntity;
	};
}

#endif // INC_SHIPDRIVER_H
