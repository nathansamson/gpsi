#ifndef INC_GAMEENTITY_H
#define INC_GAMEENTITY_H

#include "misc/vector2.h"

namespace SI {

	/**
	 * The basic of all game entities.
	*/
	class VGameEntity {
	public:
		virtual void visualize();
		virtual void update(unsigned int) = 0;
		
		Vector2 getLocation();
	protected:
		void move(Vector2);
	private:
		Vector2 fLocation;
	};
}

#endif // INC_GAMEENTTITY_H
