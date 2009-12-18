#ifndef INC_AMMOTYPE_H
#define INC_AMMOTYPE_H

#include "misc/boundingshape.h"

namespace SI {
	class AmmoType {
	public:
		virtual ~AmmoType() { delete fBoundingShapeDesc; }
		
		/**
		 * The bounding shape of the bullet.
		*/
		IBoundingShapeDescription* fBoundingShapeDesc;
	};
}

#endif // INC_AMMOTYPE_H
