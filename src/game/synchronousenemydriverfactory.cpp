#include "game/synchronousenemydriverfactory.h"
#include "game/synchronousdriver.h"

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param margin The minimal distance from the ships to the border of the game.
	*/
	SynchronousEnemyDriverFactory::SynchronousEnemyDriverFactory(double margin): fMargin(margin) {
	}
	
	/**
	 * Creates a driver.
	 *
	 * @return A driver.
	*/
	VShipDriver* SynchronousEnemyDriverFactory::createEnemyDriver() {
		return new SynchronousDriver(fMargin);
	}
}
