#ifndef INC_BUILTIN_ENEMYDRIVERFACTORY_H
#define INC_BUILTIN_ENEMYDRIVERFACTORY_H

#include <string>

#include "game/enemydriverfactory.h"

namespace SI {
	/**
	 * A factory to create builtin enemy drivers.
	*/
	class BuiltinEnemyDriverFactory: public IEnemyDriverFactory {
	public:
		virtual ~BuiltinEnemyDriverFactory() {}
		virtual VShipDriver* createEnemyDriver(std::string);
	};
}

#endif // INC_BUILTIN_ENEMYDRIVERFACTORY_H
