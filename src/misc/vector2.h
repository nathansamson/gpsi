#ifndef INC_VECTOR2_H
#define INC_VECTOR2_H

#include <iostream>

namespace si {
class Vector2 {
public:
	Vector2 ();
	Vector2 (double, double);
	
	double getX() const { return fX; };
	double getY() const { return fY; };
	void setX(double a) { fX = a; }
	void setY(double a) { fY = a; }
	
	double length() const;
	double dotProduct(const Vector2&) const;
	void normalize();
	
	Vector2 operator+(const Vector2&) const;
	Vector2& operator+=(const Vector2&);
	Vector2 operator-(const Vector2&) const;
	Vector2& operator-=(const Vector2&);
	Vector2 operator+() const;
	Vector2 operator-() const;
	
	Vector2 operator+(const double) const;
	Vector2& operator+=(const double);
	Vector2 operator-(const double) const;
	Vector2& operator-=(const double);
	Vector2 operator*(const double) const;
	Vector2& operator*=(const double);
	Vector2 operator/(const double) const;
	Vector2& operator/=(const double);
	
	bool operator==(const Vector2&) const;
	bool operator!=(const Vector2&) const;
	
private:
	double fX, fY;	
};

Vector2 operator+(const double, const Vector2&);
Vector2 operator-(const double, const Vector2&);
Vector2 operator*(const double, const Vector2&);
Vector2 operator/(const double, const Vector2&);
std::ostream& operator<<(std::ostream&, const Vector2&);

}

#endif // INC_VECTOR2_H
