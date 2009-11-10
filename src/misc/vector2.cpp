#include "vector2.h"
#include <math.h>

namespace si {

Vector2::Vector2() {
	fX = fY = 0.0;
}

Vector2::Vector2(double a, double b) {
	fX = a;
	fY = b;
}

double Vector2::length() const {
	return sqrt(fX*fX + fY*fY);
}

double Vector2::dotProduct(const Vector2& v) const {
	return fX * v.fX + fY * v.fY;
}

void Vector2::normalize() {
	double l = length();
	fX /= l;
	fY /= l;
}

Vector2 Vector2::operator+(const Vector2& w) const {
	Vector2 r = Vector2(fX+w.fX, fY+w.fY);
	return r;
}

Vector2& Vector2::operator+=(const Vector2& w) {
	fX += w.fX;
	fY += w.fY;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& w) const {
	Vector2 r = Vector2(fX-w.fX, fY-w.fY);
	return r;
}

Vector2& Vector2::operator-=(const Vector2& w) {
	fX -= w.fX;
	fY -= w.fY;
	return *this;
}

Vector2 Vector2::operator+() const {
	return *this;
}

Vector2 Vector2::operator-() const {
	Vector2 r = Vector2(-fX, -fY);
	return r;
}


Vector2 Vector2::operator+(const double a) const {
	Vector2 r = Vector2(fX+a, fY+a);
	return r;
}

Vector2& Vector2::operator+=(const double a) {
	fX += a;
	fY += a;
	return *this;
}

Vector2 Vector2::operator-(const double a) const {
	Vector2 r = Vector2(fX-a, fY-a);
	return r;
}

Vector2& Vector2::operator-=(const double a) {
	fX -= a;
	fY -= a;
	return *this;
}

Vector2 Vector2::operator*(const double a) const {
	Vector2 r = Vector2(fX*a, fY*a);
	return r;
}

Vector2& Vector2::operator*=(const double a) {
	fX *= a;
	fY *= a;
	return *this;
}

Vector2 Vector2::operator/(const double a) const {
	Vector2 r = Vector2(fX/a, fY/a);
	return r;
}

Vector2& Vector2::operator/=(const double a) {
	fX /= a;
	fY /= a;
	return *this;
}

bool Vector2::operator==(const Vector2& w) const {
	return (fX == w.fX && fY == w.fY);
}

bool Vector2::operator!=(const Vector2& w) const {
	return (fX != w.fX && fY != w.fY);
}

Vector2 operator+(const double a, const Vector2& v) {
	Vector2 r = Vector2(v.getX()+a, v.getY()+a);
	return r;
}

Vector2 operator-(const double a, const Vector2& v) {
	Vector2 r = Vector2(v.getX()-a, v.getY()-a);
	return r;
}

Vector2 operator*(const double a, const Vector2& v) {
	Vector2 r = Vector2(v.getX()*a, v.getY()*a);
	return r;
}

std::ostream& operator<<(std::ostream& s, const Vector2& v) {
	s << "<" << v.getX() << ", " << v.getY() << ">";
	return s;
}

}
