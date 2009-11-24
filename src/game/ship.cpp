#include "ship.h"

namespace SI {
	Ship::Ship(Vector2 speed): fSpeed(speed) {
	}
	
	void Ship::update(int ticks) {
		if (ticks < 0) {
			throw -ticks;
		}
		move(fSpeed * ticks);
	}
}
