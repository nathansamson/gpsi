#include "gameentity.h"

namespace SI {
	/**
	 * Public constructor.
	*/
	VGameEntity::VGameEntity(): fPosition(Vector2(0, 0)) {
	}
	
	/**
	 * Public constructor.
	 *
	 * @param pos The initial position of the entity.
	*/
	VGameEntity::VGameEntity(Vector2 pos): fPosition(pos) {
	}
	
	/**
	 * Desctructor.
	*/
	VGameEntity::~VGameEntity() {
	}

	/**
	 * Get the position of the entity.
	 * @return The position of the entity. The position is the position of the center of the entity.
	*/
	Vector2 VGameEntity::getPosition() {
		return fPosition;
	}
	
	/**
	 * Move the entity with a specified offset.
	 *
	 * @param v The offset to move the entity.
	*/
	void VGameEntity::move(Vector2 v) {
		fPosition += v;
	}
	
	/**
	 * Visualize the entity. The VGameEntity will do nothing.
	*/
	void VGameEntity::visualize() {
	}
}
