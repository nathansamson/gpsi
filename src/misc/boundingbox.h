#ifndef INC_BOUNDINGBOX_H
#define INC_BOUNDINGBOX_H

/** \file
 * File for the bounding boxes.
 *
 * @author Nathan Samson
*/

#include "misc/boundingshape.h"

namespace SI {
	class BoundingBox;
	
	/**
	 * A blueprint for a bounding box.
	*/
	class BoundingBoxDescription: public IBoundingShapeDescription {
	public:
		BoundingBoxDescription(double, double);
		BoundingBoxDescription(const BoundingBoxDescription&);
		virtual BoundingBoxDescription* copy();
		virtual VBoundingShape* createShape();
		
		virtual double getWidth();
		double getHeight();
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

	/**
	 * A rectangulare bounding shape.
	*/
	class BoundingBox: public VBoundingShape {
	public:
		BoundingBox(BoundingBoxDescription*);
	
		virtual bool intersects(VBoundingShape*);
		
		virtual double getWidth();
		virtual double getHeight();
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
