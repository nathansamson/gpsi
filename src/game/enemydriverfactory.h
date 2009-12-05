#ifndef INC_ENEMYDRIVERFACTORY_H
#define INC_ENEMYDRIVERFACTORY_H

#include "game/shipdriver.h"

namespace SI {
	class IEnemyDriverFactory {
	public:
		virtual ~IEnemyDriverFactory() {}
		virtual VShipDriver* createEnemyDriver() = 0;
	};
}

#endif // INC_ENEMYDRIVERFACTORY_H
