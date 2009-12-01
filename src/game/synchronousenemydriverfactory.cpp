#include "game/synchronousenemydriverfactory.h"
#include "game/synchronousdriver.h"

namespace SI {
	SynchronousEnemyDriverFactory::SynchronousEnemyDriverFactory(double margin): fMargin(margin) {
	}
	
	VShipDriver* SynchronousEnemyDriverFactory::createEnemyDriver() {
		return new SynchronousDriver(fMargin);
	}
}
