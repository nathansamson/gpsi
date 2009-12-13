#include "game/builtinenemydriverfactory.h"
#include "game/synchronousdriver.h"

namespace SI {
	/**
	 * Creates a driver.
	 *
	 * @return A driver.
	*/
	VShipDriver* BuiltinEnemyDriverFactory::createEnemyDriver(std::string name) {
		if (name == "syncdriver") {
			return new SynchronousDriver(1.5);
		} else {
			return 0;
		}
	}
}
