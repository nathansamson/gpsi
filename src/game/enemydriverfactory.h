#ifndef INC_ENEMYDRIVERFACTORY_H
#define INC_ENEMYDRIVERFACTORY_H

#include "game/shipdriver.h"

namespace SI {
	/**
	 * Interface for enemy driver factories.
	*/
	class IEnemyDriverFactory {
	public:
		virtual ~IEnemyDriverFactory() {}
		/**
		 * Creates an enemy driver.
		*/
		virtual VShipDriver* createEnemyDriver(std::string) = 0;
	};
}

#endif // INC_ENEMYDRIVERFACTORY_H
