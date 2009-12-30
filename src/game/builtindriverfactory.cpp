/** \file
 * File for the builtin driver factory.
 *
 * @author Nathan Samson
*/

#include <cstdlib>

#include "game/builtindriverfactory.h"
#include "game/synchronousdriver.h"
#include "game/demodriver.h"

namespace SI {
	VShipDriver* BuiltinDriverFactory::createUserDriver() {
		return new DemoDriver();
	}

	/**
	 * Creates a driver.
	 *
	 * @return A driver.
	*/
	VShipDriver* BuiltinDriverFactory::createEnemyDriver(std::string name,
	                   std::map<std::string, std::string> atts) {
		if (name == "syncdriver") {
			int count = atoi(atts["count"].c_str());
			if (atts["packed"] == "packed") {
				// They can move
				// (8 - width * count) / 2
				double width = 0.80;
				double offset;
				if (atts["align"] == "center") {
					offset = 0.0;
				} else {
					offset = atof(atts["align"].c_str());
				}
				return new SynchronousDriver((8 - width * count) / 2, offset);
			} else {
				// They can move
				// 8 - 2 * margin / count
				double margin = atof(atts["margin"].c_str());
				return new SynchronousDriver((8 - 2 * margin) / (2 * count));
			}
		} else {
			return 0;
		}
	}
}
