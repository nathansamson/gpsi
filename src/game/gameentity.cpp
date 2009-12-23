#include "game/gameentity.h"
#include "misc/boundingbox.h"

namespace SI {	
	/**
	 * Public constructor.
	 *
	 * @param pos The initial position of the entity.
	 * @param dir The direction of the entity.
	 * @param bshape The bounding shape of the entity. The entity owns the bounding shape.
	 * @param group The group of the entity.
	 * @param fac The factory that created this entity.
	*/
	VGameEntity::VGameEntity(Vector2 pos, int dir, IBoundingShapeDescription* bshape,
	                         EntityGroup* group, IGameEntityFactory* fac):
	             fEntityFactory(fac), fGroup(group), fPosition(pos), fDirection(dir),
	             fBoundingShape(bshape->createShape()), fDead(false) {
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
	 * Returns the direction of the ship.
	 *
	 * A value of 0 means upwards directed. A higher value means it is rotated clockwise. A value of 360 is a full rotation.
	*/
	int VGameEntity::getDirection() {
		return fDirection;
	}
	
	/**
	 * Returns the group of the entity.
	 *
	 * @return The group of the entity.
	*/
	EntityGroup* VGameEntity::getGroup() {
		return fGroup;
	}
	
	/**
	 * Collides the entity with another object.
	 * If they collide, the collide() functions will be called of the 2 entities.
	 *
	 * @param o
	*/
	void VGameEntity::checkCollision(VGameEntity* o) {
		if (fGroup == o->fGroup) {
			return;
		}
		if (fBoundingShape->intersects(o->fBoundingShape)) {
			this->collide(o);
			o->collide(this);
		}
	}
	
	/**
	 * Checks if the entity is dead.
	 *
	 * @return True if the entity is dead.
	*/
	bool VGameEntity::isDead() {
		return fDead;
	}
	
	/**
	 * Let the entity die.
	*/
	void VGameEntity::die() {
		fDead = true;
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
	
	/**
	 * Checks if an entity crosses a given line (parallel with the x-axis)
	 *
	 * @param y The y-coordinate of the line.
	 *
	 * @return True if the entity crosses the line.
	*/
	bool VGameEntity::crossesLine(double y) {
		BoundingBoxDescription boxDesc(8, 0.01); // Create a line
		BoundingBox* box = new BoundingBox(&boxDesc);
		box->setOffset(Vector2(-4.0, y));
		bool crosses = box->intersects(fBoundingShape);
		delete box;
		return crosses;
	}
}
