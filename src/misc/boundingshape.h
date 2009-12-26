#ifndef INC_BOUNDINGSHAPE_H
#define INC_BOUNDINGSHAPE_H

/** \file
 * File for the bounding shape.
 *
 * @author Nathan Samson
*/

#include "misc/vector2.h"

namespace SI {
	/**
	 * A generic bounding shape.
	*/
	class VBoundingShape {
	public:
		VBoundingShape();
	
		/**
		 * Checks if 2 bounding shapes intersects with each other.
		 *
		 * @return True if the 2 bounding shapes intersects.
		*/
		virtual bool intersects(VBoundingShape*) = 0;
		/**
		 * Checks if 2 bounding shapes intersects with each other.
		 *
		 * @return True if the 2 bounding shapes intersects.
		*/
		virtual bool intersects(VBoundingShape*, bool) = 0;
		
		void setOffset(Vector2);
	protected:

		/**
		 * The offset of the shape. The offset is always the center of the 
		 * complete surrounding rectangular box of the bounding shape.
		*/
		Vector2 fOffset;
	};
	
	/**
	 * Generic blueprint for a bounding shape.
	*/
	class IBoundingShapeDescription {
	public:
		/**
		 * Creates the shape from the description.
		 *
		 * @return The bounding shape created from the blueprint.
		*/
		virtual VBoundingShape* createShape() = 0;
	};
	
	/**
	 * Exception thrown when their is no algorithm found to check the intersection of 2 shapes.
	*/
	class UnresolvedIntersectionException {
	public:
		/**
		 * Public constructor.
		 *
		 * @param f The first shape.
		 * @param s The second shape.
		*/
		UnresolvedIntersectionException(VBoundingShape* f, VBoundingShape* s):
		     first(f), second(s) {
		}
		
		/**
		 * The first shape.
		*/
		VBoundingShape* first;
		/**
		 * The second shape.
		*/
		VBoundingShape* second;
	};
}

#endif // INC_BOUNDINGSHAPE_H
