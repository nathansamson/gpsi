#include "shipdriver.h"

namespace SI {

	VShipDriver::VShipDriver(): fEntity(0) {
	}
	
	void VShipDriver::bind(Ship* e) {
		fEntity = e;
	}
	
	void VShipDriver::move(Vector2 v) {
		fEntity->move(v);
	}
}
