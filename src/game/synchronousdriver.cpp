#include <cmath>

#include "game/synchronousdriver.h"

namespace SI {
	SynchronousDriver::SynchronousDriver(double xMargin): fXMargin(xMargin), fMoved(0.0, 0.0), fDir(1) {
	}
	
	void SynchronousDriver::update(int ticks) {
		Vector2 step = Vector2(fDir*0.0002*ticks, -0.0001*ticks);
		fMoved += step;
		if (std::fabs(fMoved.getX()) > fXMargin) {
			fDir *= -1;
			step -= step;
		}
		move(step);
	}
}
