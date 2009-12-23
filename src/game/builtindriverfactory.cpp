#include <cstdlib>

#include "game/builtindriverfactory.h"
#include "game/synchronousdriver.h"

namespace SI {
	/**
	 * Creates a driver.
	 *
	 * @return A driver.
	*/
	VShipDriver* BuiltinDriverFactory::createEnemyDriver(std::string name,
	                   std::map<std::string, std::string> atts) {
		if (name == "syncdriver") {
			// They can move
			// 8 - 2 * margin / count
			double margin = atof(atts["margin"].c_str());
			int count = atoi(atts["count"].c_str());
			return new SynchronousDriver((8 - 2 * margin) / (2 * count));
		} else {
			return 0;
		}
	}
}
