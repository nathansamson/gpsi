#include "ship.h"

namespace SI {
	Ship::Ship(int strength): fStrength(strength), fSpeed(1.0/1000, 0.0) {
	}
	
	void Ship::update(unsigned int ticks) {
		move(fSpeed * ticks);
	}
}
