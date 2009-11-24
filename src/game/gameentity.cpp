#include "gameentity.h"

namespace SI {
	Vector2 VGameEntity::getLocation() {
		return fLocation;
	}
	
	void VGameEntity::move(Vector2 v) {
		fLocation += v;
	}
}
