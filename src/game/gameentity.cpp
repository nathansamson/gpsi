#include "gameentity.h"

namespace SI {	
	/**
	 * Public constructor.
	 *
	 * @param pos The initial position of the entity.
	 * @param bshape The bounding shape of the entity. The entity owns the bounding shape.
	 * @param fac The factory that created this entity.
	*/
	VGameEntity::VGameEntity(Vector2 pos, IBoundingShapeDescription* bshape,
	                         IGameEntityFactory* fac):
	             fEntityFactory(fac), fPosition(pos), fBoundingShape(bshape->createShape()) {
		fBoundingShape->setOffset(pos);
	}
	
	/**
	 * Desctructor.
	*/
	VGameEntity::~VGameEntity() {
		delete fBoundingShape;
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
		fBoundingShape->setOffset(fPosition);
	}
	
	/**
	 * Visualize the entity. The VGameEntity will do nothing.
	*/
	void VGameEntity::visualize() {
	}
}
