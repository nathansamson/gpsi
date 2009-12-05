#ifndef INC_BOUNDINGBOX_H
#define INC_BOUNDINGBOX_H

#include "misc/boundingshape.h"

namespace SI {
	/**
	 * A rectangulare bounding shape.
	*/
	class BoundingBox: public VBoundingShape {
	public:
		BoundingBox(double, double);
	
		virtual bool intersects(VBoundingShape*);
	protected:
		virtual bool intersects(VBoundingShape*, bool);
	private:
		/**
		 * The width of the box.
		*/
		double fW;
		
		/**
		 * The height of the box.
		*/
		double fH;
	};
}

#endif // INC_BOUNDINGBOX_H
