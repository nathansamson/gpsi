#ifndef INC_VECTOR2_H
#define INC_VECTOR2_H

/** \file
 * File for the vector.
 *
 * @author Nathan Samson
*/

#include <iostream>

namespace SI {
	/**
	 * Class to represent a vector.
	 *
	 * Can be used as point vector (location in 2D space), or as normal vector (like a speed vector).
	*/
	class Vector2 {
	public:
		Vector2 ();
		Vector2 (const Vector2&);
		Vector2 (double, double);
		Vector2 operator=(const Vector2&);
	
		/**
		 * Get the X value of the vector.
		 *
		 * @return The X value of the vector.
		*/
		double getX() const { return fX; };
		
		/**
		 * Get the Y value of the vector.
		 *
		 * @return The X value of the vector.
		*/
		double getY() const { return fY; };
		
		/**
		 * Set the X value for the vector.
		 *
		 * @param a The new X value.
		*/
		void setX(double a) { fX = a; }
		
		/**
		 * Set the Y value for the vector.
		 *
		 * @param a The new Y value.
		*/
		void setY(double a) { fY = a; }
		
		double length() const;
		double dotProduct(const Vector2&) const;
		void normalize();
		Vector2 rotate(int);
		void inBounds(Vector2 maxBound, Vector2 minBound);
		
		Vector2 operator+(const Vector2&) const;
		Vector2& operator+=(const Vector2&);
		Vector2 operator-(const Vector2&) const;
		Vector2& operator-=(const Vector2&);
		Vector2 operator+() const;
		Vector2 operator-() const;
	
		Vector2 operator+(const double&) const;
		Vector2& operator+=(const double&);
		Vector2 operator-(const double&) const;
		Vector2& operator-=(const double&);
		Vector2 operator*(const double&) const;
		Vector2& operator*=(const double&);
		Vector2 operator/(const double&) const;
		Vector2& operator/=(const double&);
		
		bool operator==(const Vector2&) const;
		bool operator!=(const Vector2&) const;
	
	private:
		/**
		 * X value of the vector.
		*/
		double fX;
	
		/**
		 * Y value of the vector.
		*/
		double fY;
	};
	
	Vector2 operator+(const double&, const Vector2&);
	Vector2 operator-(const double&, const Vector2&);
	Vector2 operator*(const double&, const Vector2&);
	Vector2 operator/(const double&, const Vector2&);
	std::ostream& operator<<(std::ostream&, const Vector2&);

}

#endif // INC_VECTOR2_H
