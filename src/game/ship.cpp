#include "ship.h"

namespace SI {
	Ship::Ship(VShipController* moveController): fMoveController(moveController) {
		fMoveController->bind(this, &VGameEntity::move);
	}
	
	Ship::~Ship() {
		delete fMoveController;
	}
	
	void Ship::update(int ticks) {
		if (ticks < 0) {
			throw -ticks;
		}
		fMoveController->update(ticks);
	}
}
