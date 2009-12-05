#ifndef INC_SYNC_ENEMYDRIVERFACTORY_H
#define INC_SYNC_ENEMYDRIVERFACTORY_H

#include "game/enemydriverfactory.h"

namespace SI {
	/**
	 * A factory to create synchronous enemy drivers.
	*/
	class SynchronousEnemyDriverFactory: public IEnemyDriverFactory {
	public:
		SynchronousEnemyDriverFactory(double);
		
		virtual VShipDriver* createEnemyDriver();
	private:
		/**
		 * The minimal distance to the border of the field.
		*/
		double fMargin;
	};
}

#endif // INC_SYNC_ENEMYDRIVERFACTORY_H
