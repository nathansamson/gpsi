#ifndef INC_GAMEENTITY_H
#define INC_GAMEENTITY_H

#include "misc/vector2.h"

namespace SI {

	/**
	 * The base class of all game entities.
	*/
	class VGameEntity {
	public:
		VGameEntity();
		VGameEntity(Vector2 );
		virtual ~VGameEntity();
	
		virtual void visualize();
		
		/**
		 * Update the state of the entity.
		*/
		virtual void update(int) = 0;
		
		Vector2 getPosition();
	protected:
		void move(Vector2);
	private:
		/**
		 * The position of the center of the entity.
		*/
		Vector2 fPosition;
	};
}

#endif // INC_GAMEENTTITY_H
