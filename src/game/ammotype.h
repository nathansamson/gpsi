#ifndef INC_AMMOTYPE_H
#define INC_AMMOTYPE_H

/** \file
 * File for the ammunition type.
 *
 * @author Nathan Samson
*/

#include "misc/boundingshape.h"

namespace SI {
	/**
	 * Base type for ammunition types.
	*/
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
