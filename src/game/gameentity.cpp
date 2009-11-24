#include "gameentity.h"

namespace SI {
	VGameEntity::VGameEntity(): fPosition(Vector2(0, 0)) {
	}
	
	VGameEntity::VGameEntity(Vector2 pos): fPosition(pos) {
	}
	
	VGameEntity::~VGameEntity() {
	}

	Vector2 VGameEntity::getPosition() {
		return fPosition;
	}
	
	void VGameEntity::move(Vector2 v) {
		fPosition += v;
	}
	
	void VGameEntity::visualize() {
	}
}
