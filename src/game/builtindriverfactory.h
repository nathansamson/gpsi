#ifndef INC_BUILTIN_DRIVERFACTORY_H
#define INC_BUILTIN_DRIVERFACTORY_H

#include <string>

#include "game/driverfactory.h"

namespace SI {
	/**
	 * A factory to create builtin enemy drivers.
	*/
	class BuiltinDriverFactory: public IDriverFactory {
	public:
		virtual ~BuiltinDriverFactory() {}
		virtual VShipDriver* createEnemyDriver(std::string, std::map<std::string, std::string>);
	};
}

#endif // INC_BUILTIN_ENEMYDRIVERFACTORY_H
