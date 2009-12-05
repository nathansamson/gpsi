#include "misc/boundingshape.h"

namespace SI {
	/**
	 * Public constructor.
	*/
	VBoundingShape::VBoundingShape(): fOffset(Vector2(0.0, 0.0)) {
	}
	
	/**
	 * Sets the offset of the shape.
	 *
	 * The offset is always the center of the 
	 * complete surrounding rectangular box of the bounding shape.
	*/
	void VBoundingShape::setOffset(Vector2 offset) {
		fOffset = offset;
	}
}
