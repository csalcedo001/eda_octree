#include "vector.hpp"

#include <cmath>

namespace eda {

namespace octree {

Vector::Vector(int x, int y, int z) :
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
