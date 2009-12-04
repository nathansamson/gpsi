#ifndef INC_GAMEENTITY_H
#define INC_GAMEENTITY_H

#include <vector>

#include "misc/vector2.h"

namespace SI {
	class IGameEntityFactory;

	/**
	 * The base class of all game entities.
	*/
	class VGameEntity {
	public:
		VGameEntity(Vector2, IGameEntityFactory*);
		virtual ~VGameEntity();
	
		virtual void visualize();
		
		/**
		 * Update the state of the entity.
		*/
		virtual std::vector<VGameEntity*> update(int) = 0;
		
		Vector2 getPosition();
	protected:
		void move(Vector2);
		
		/**
		 * The entity factory that created this entity.
		*/
		IGameEntityFactory* fEntityFactory;
	private:
		/**
		 * The position of the center of the entity.
		*/
		Vector2 fPosition;
	};
}

#endif // INC_GAMEENTTITY_H
