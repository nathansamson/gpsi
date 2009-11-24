#ifndef INC_SHIPCONTROLLER_H
#define INC_SHIPCONTROLLER_H

#include "gameentity.h"
#include "misc/vector2.h"

namespace SI {
	class VShipController {
	public:
		VShipController();
			
		virtual void update(int) = 0;
		void bind(VGameEntity*, void (VGameEntity::* )(Vector2));
	protected:
		void move(Vector2);
	private:
		VGameEntity* fEntity;
		void (VGameEntity::* fMoveCallback)(Vector2);
	};
}

#endif // INC_SHIPCONTROLLER_H
