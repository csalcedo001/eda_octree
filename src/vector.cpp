#include "vector.hpp"

#include <cmath>

namespace eda {

namespace octree {

Vector::Vector(double x, double y, double z) :
	x(x),
	y(y),
	z(z)
{ }

Vector::Vector(const Vector &v) :
	x(v.x),
	y(v.y),
	z(v.z)
{ }

double Vector::length() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector::rotate_x(double angle) {
	double y, z;

	y = this->y * cos(angle) - this->z * sin(angle);
	z = this->y * sin(angle) + this->z * cos(angle);

	this->y = y;
	this->z = z;
}

void Vector::rotate_y(double angle) {
	double x, z;

	x = this->x * cos(angle) + this->z * sin(angle);
	z = -this->x * sin(angle) + this->z * cos(angle);

	this->x = x;
	this->z = z;
}

void Vector::rotate_z(double angle) {
	double x, y;

	x = this->x * cos(angle) - this->y * sin(angle);
	y = this->x * sin(angle) + this->y * cos(angle);

	this->x = x;
	this->y = y;
}

Vector Vector::operator+(Vector v) {
	return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector Vector::operator-(Vector v) {
	return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector Vector::operator*(double c) {
	return Vector(this->x * c, this->y * c, this->z * c);
}

Vector Vector::operator/(double c) {
	return Vector(this->x / c, this->y / c, this->z / c);
}

} // namespace octree

} // namespace eda
