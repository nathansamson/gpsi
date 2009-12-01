#ifndef INC_SYNCHRONOUSDRIVER_H
#define INC_SYNCHRONOUSDRIVER_H

#include "game/shipdriver.h"

namespace SI {
	class SynchronousDriver: public VShipDriver {
	public:
		SynchronousDriver(double);
		
		virtual void update(int);
	private:
		double fXMargin;
		Vector2 fMoved;
		int fDir;
	};
}

#endif // INC_SYNCHRONOUSDRIVER_H
