#ifndef INC_SYNC_ENEMYDRIVERFACTORY_H
#define INC_SYNC_ENEMYDRIVERFACTORY_H

#include "game/enemydriverfactory.h"

namespace SI {
	class SynchronousEnemyDriverFactory: public IEnemyDriverFactory {
	public:
		SynchronousEnemyDriverFactory(double);
		
		virtual VShipDriver* createEnemyDriver();
	private:
		double fMargin;
	};
}

#endif // INC_SYNC_ENEMYDRIVERFACTORY_H
