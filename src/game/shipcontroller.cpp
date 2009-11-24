#include "shipcontroller.h"

namespace SI {

	VShipController::VShipController(): fEntity(0), fMoveCallback(0) {
	}
	
	void VShipController::bind(VGameEntity* e, void (VGameEntity::* f)(Vector2)) {
		fEntity = e;
		fMoveCallback = f;
	}
	
	void VShipController::move(Vector2 v) {
		(fEntity->*fMoveCallback)(v);
	}
}
