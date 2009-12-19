#include "misc/vector2.h"
#include <math.h>

#define PI 3.14159265

namespace SI {

	/**
	 * Default constructor.
	*/
	Vector2::Vector2() {
		fX = fY = 0.0;
	}
	
	/**
	 * Copy constructor.
	 *
	 * @param v The vector to copy.
	*/
	Vector2::Vector2(const Vector2& v) : fX(v.fX), fY(v.fY) {
	}
	
	/**
	 * Constructor to initialize the length of the vector.
	 *
	 * @param x The X value of the vector.
	 * @param y The Y value of the vector.
	*/
	Vector2::Vector2(double x, double y) : fX(x), fY(y) {
	}
	
	/**
	 * Assignment operator.
	 *
	 * @param rhs The right hand side of the assignment.
	 * @return The assigned value.
	*/
	Vector2 Vector2::operator=(const Vector2& rhs) {
		fX = rhs.fX;
		fY = rhs.fY;
		return *this;
	}
	
	/**
	 * Calculates the length (norm) of the vector.
	 *
	 * @return The length of the vector.
	*/
	double Vector2::length() const {
		return sqrt(fX*fX + fY*fY);
	}
	
	/**
	 * Calculates the dot prodcut of this vector with another vector.
	 *
	 * @param v The other vector.
	 *
	 * @return The dot product of this vector and vector v.
	*/
	double Vector2::dotProduct(const Vector2& v) const {
		return fX * v.fX + fY * v.fY;
	}
	
	/**
	 * Normalizes the vector.
	 *
	 * Set the length of the vector to 1.
	*/
	void Vector2::normalize() {
		double l = length();
		fX /= l;
		fY /= l;
	}
	
	Vector2 Vector2::rotate(int degrees) {
		double sinTheta = sin(degrees * PI / 180);
		double cosTheta = cos(degrees * PI / 180);
		
		return Vector2(fX * cosTheta - fY * sinTheta,
		               fX * sinTheta + fY * cosTheta);
	}
	
	/**
	 * The + operator.
	 *
	 * @param w The second argument for the + operation.
	 * @return The sum of this vector and vector w.
	*/
	Vector2 Vector2::operator+(const Vector2& w) const {
		Vector2 r = Vector2(fX+w.fX, fY+w.fY);
		return r;
	}
	
	/**
	 * The += operator.
	 *
	 * Add the vector w to this vector.
	 *
	 * @param w The second argument for the += operation.
	 * @return The sum of this vector and vector w.
	*/
	Vector2& Vector2::operator+=(const Vector2& w) {
		fX += w.fX;
		fY += w.fY;
		return *this;
	}
	
	/**
	 * The - operator.
	 *
	 * @param w The second argument for the - operation.
	 * @return The difference of this vector and vector w.
	*/
	Vector2 Vector2::operator-(const Vector2& w) const {
		Vector2 r = Vector2(fX-w.fX, fY-w.fY);
		return r;
	}
	
	/**
	 * The -= operator.
	 *
	 * Subtracts the vector w from this vector.
	 *
	 * @param w The second argument for the -= operation.
	 * @return The difference of this vector and vector w.
	*/
	Vector2& Vector2::operator-=(const Vector2& w) {
		fX -= w.fX;
		fY -= w.fY;
		return *this;
	}
	
	/**
	 * The unary + operator.
	 *
	 * @return The current vector.
	*/
	Vector2 Vector2::operator+() const {
		return *this;
	}
	
	/**
	 * The unary - operator.
	 *
	 * @return The opposite of the current vector.
	*/
	Vector2 Vector2::operator-() const {
		Vector2 r = Vector2(-fX, -fY);
		return r;
	}
	
	/**
	 * The + operator.
	 *
	 * Calculates the sum of this vector and scalar a.
	 * This is the same as calculating the sum of this vector and Vector2(a, a).
	 *
	 * @param a The scalar a.
	 * @return The sum of this vector and the scalar a.
	*/
	Vector2 Vector2::operator+(const double& a) const {
		Vector2 r = Vector2(fX+a, fY+a);
		return r;
	}
	
	/**
	 * The += operator.
	 *
	 * Adds the scalar a to this vector.
	 * This is the same as adding this vector and Vector2(a, a).
	 *
	 * @param a The scalar a.
	 * @return The sum of this vector and the scalar a.
	*/
	Vector2& Vector2::operator+=(const double& a) {
		fX += a;
		fY += a;
		return *this;
	}
	
	/**
	 * The - operator.
	 *
	 * Calculates the difference of this vector and scalar a.
	 * This is the same as calculating the difference of this vector and Vector2(a, a).
	 *
	 * @param a The scalar a.
	 * @return The difference of this vector and the scalar a.
	*/
	Vector2 Vector2::operator-(const double& a) const {
		Vector2 r = Vector2(fX-a, fY-a);
		return r;
	}
	
	/**
	 * The -= operator.
	 *
	 * Subtracts the scalar a from to this vector.
	 * This is the same as adding this vector and Vector2(a, a).
	 *
	 * @param a The scalar a.
	 * @return The difference of this vector and the scalar a.
	*/
	Vector2& Vector2::operator-=(const double& a) {
		fX -= a;
		fY -= a;
		return *this;
	}
	
	/**
	 * The * operator.
	 *
	 * Multiplies the vector with a scalar a.
	 *
	 * @param a The scalar
	 * @return this vector multiplied with a.
	*/
	Vector2 Vector2::operator*(const double& a) const {
		Vector2 r = Vector2(fX*a, fY*a);
		return r;
	}
	
	/**
	 * The *= operator.
	 *
	 * Multiplies the scalar a to this vector.
	 * This is the same as multiplying this vector and Vector2(a, a).
	 *
	 * @param a The scalar a.
	 * @return The multiplication of this vector and the scalar a.
	*/
	Vector2& Vector2::operator*=(const double& a) {
		fX *= a;
		fY *= a;
		return *this;
	}
	
	/**
	 * The / operator.
	 *
	 * Divides the vector with a scalar a.
	 *
	 * @param a The scalar
	 * @return this vector divided with a.
	*/
	Vector2 Vector2::operator/(const double& a) const {
		Vector2 r = Vector2(fX/a, fY/a);
		return r;
	}
	
	/**
	 * The *= operator.
	 *
	 * Divides the scalar a to this vector.
	 * This is the same as dividing this vector and Vector2(a, a).
	 *
	 * @param a The scalar a.
	 * @return The division of this vector and the scalar a.
	*/
	Vector2& Vector2::operator/=(const double& a) {
		fX /= a;
		fY /= a;
		return *this;
	}
	
	/**
	 * Checks the equality of 2 vectors.
	 *
	 * @param w The other vector w.
	 * @return True if this is equal to w, false if not.
	*/
	bool Vector2::operator==(const Vector2& w) const {
		return (fX == w.fX && fY == w.fY);
	}
	
	/**
	 * Checks the inequality of 2 vectors.
	 *
	 * @param w The other vector w.
	 * @return False if this is equal to w, true if not.
	*/
	bool Vector2::operator!=(const Vector2& w) const {
		return (fX != w.fX && fY != w.fY);
	}
	
	/**
	 * The + operator.
	 *
	 * Calculates the sum of a vector v and scalar a.
	 * This is the same as adding to both the X and Y values of v with a.
	 *
	 * @param a The scalar a.
	 * @param v The vector v.
	 * @return The sum of vector v and the scalar a.
	*/
	Vector2 operator+(const double& a, const Vector2& v) {
		Vector2 r = Vector2(v.getX()+a, v.getY()+a);
		return r;
	}
	
	/**
	 * The - operator.
	 *
	 * Calculates the difference of a vector v and scalar a.
	 * This is the same as subtracting both the X and Y values of v with a.
	 *
	 * @param a The scalar a.
	 * @param v The vector v.
	 * @return The difference of vector v and the scalar a.
	*/
	Vector2 operator-(const double& a, const Vector2& v) {
		Vector2 r = Vector2(v.getX()-a, v.getY()-a);
		return r;
	}
	
	/**
	 * The + operator.
	 *
	 * Calculates the multiplication of a vector v and scalar a.
	 * This is the same as multiplying both the X and Y values of v with a.
	 *
	 * @param a The scalar a.
	 * @param v The vector v.
	 * @return The multiplication of vector v and the scalar a.
	*/
	Vector2 operator*(const double& a, const Vector2& v) {
		Vector2 r = Vector2(v.getX()*a, v.getY()*a);
		return r;
	}
	
	/**
	 * The + operator.
	 *
	 * Calculates the division of a vector v and scalar a.
	 * This is the same as dividing both the X and Y values of v with a.
	 *
	 * @param a The scalar a.
	 * @param v The vector v.
	 * @return The multiplication of vector v and the scalar a.
	*/
	Vector2 operator/(const double& a, const Vector2& v) {
		Vector2 r = Vector2(v.getX()/a, v.getY()/a);
		return r;
	}
	
	/**
	 * Write the vector to a stream.
	 *
	 * Mainly used for debugging purposes.
	 *
	 * @param s The output stream.
	 * @param v The vector to output.
	*/
	std::ostream& operator<<(std::ostream& s, const Vector2& v) {
		s << "<" << v.getX() << ", " << v.getY() << ">";
		return s;
	}

}
