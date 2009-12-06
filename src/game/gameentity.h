#ifndef INC_GAMEENTITY_H
#define INC_GAMEENTITY_H

#include <vector>

#include "misc/vector2.h"
#include "misc/boundingshape.h"
#include "game/entitygroup.h"

namespace SI {
	class IGameEntityFactory;

	/**
	 * The base class of all game entities.
	*/
	class VGameEntity {
	public:
		VGameEntity(Vector2, int, IBoundingShapeDescription*, EntityGroup*, IGameEntityFactory*);
		virtual ~VGameEntity();
	
		virtual void visualize();
		
		/**
		 * Update the state of the entity.
		*/
		virtual std::vector<VGameEntity*> update(int) = 0;
		
		Vector2 getPosition();
		int getDirection();
	protected:
		void move(Vector2);
		
		/**
		 * The entity factory that created this entity.
		*/
		IGameEntityFactory* fEntityFactory;
		
		/**
		 * The group of the entity.
		*/
		EntityGroup* fGroup;
	private:
		/**
		 * The position of the center of the entity.
		*/
		Vector2 fPosition;
		
		/**
		 * The direction of the entity. 0 is up, moure is clockwise rotated. 360 is a full rotation (= 0).
		*/
		int fDirection;
		
		/**
		 * The bounding shape of the entity.
		*/
		VBoundingShape* fBoundingShape;
	};
}

#endif // INC_GAMEENTTITY_H
