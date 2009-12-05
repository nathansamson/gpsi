#include <typeinfo>
#include "misc/boundingbox.h"

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param w The width of the box.
	 * @param h The height of the box.
	*/
	BoundingBox::BoundingBox(double w, double h): fW(w), fH(h) {
	}
	
	/**
	 * Checks if the box intersects with another shape.
	 *
	 * @param other The other shape.
	 * @return True if they intersect, false if not.
	 *
	 * @throw UnresolvedIntersectionException if box could not find a method to calculate the intersection with o.
	*/
	bool BoundingBox::intersects(VBoundingShape* other) {
		return intersects(other, true);
	}
	
	/**
	 * Checks if the box intersects with another shape.
	 *
	 * @param o The other shape.
	 * @param recursive If true and the box does not know what to do with o, we ask o to check intersections with the box.
	 * @throw UnresolvedIntersectionException if box could not find a method to calculate the intersection with o.
	*/
	bool BoundingBox::intersects(VBoundingShape* o, bool recursive) {
		if (typeid (*o) == typeid(*this)) {
			BoundingBox* other = static_cast<BoundingBox*>(o);
			double thisX = fOffset.getX() - fW / 2;
			double thisY = fOffset.getY() - fH / 2;
			
			double otherX = other->fOffset.getX() - other->fW / 2;
			double otherY = other->fOffset.getY() - other->fH / 2;
			
			if (thisX + fW < otherX || thisY + fH < otherY ||
			    otherX + other->fW < thisX || otherY + other->fH < thisY) {
				return false;
			} else {
				return true;
			}
		} else {
			if (recursive) {
				return o->intersects(this, false);
			} else {
				throw UnresolvedIntersectionException(o, this);
			}
		}
	}
}
