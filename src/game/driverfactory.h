#ifndef INC_DRIVERFACTORY_H
#define INC_DRIVERFACTORY_H

#include <map>
#include "game/shipdriver.h"

namespace SI {
	/**
	 * Interface for enemy driver factories.
	*/
	class IDriverFactory {
	public:
		virtual ~IDriverFactory() {}
		
		/**
		 * Creates a user driver.
		*/
		virtual VShipDriver* createUserDriver() = 0;
		
		/**
		 * Creates an enemy driver.
		*/
		virtual VShipDriver* createEnemyDriver(std::string, std::map<std::string, std::string>) = 0;
	};
}

#endif // INC_ENEMYDRIVERFACTORY_H
