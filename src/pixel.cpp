#include "pixel.hpp"

#include <fstream>

namespace eda {

namespace octree {

Pixel::Pixel(const Pixel &pixel) :
	r(pixel.r),
	g(pixel.g),
	b(pixel.b)
{ }

Pixel::Pixel(int r, int g, int b) :
	r(r),
	g(g),
	b(b)
{ }

Pixel::Pixel(int b) :
	r(b),
	g(b),
	b(b)
{ }

double Pixel::average() {
	return (this->r + this->g + this->b) / 3.0;
}

std::ostream& operator<<(std::ostream &os, const Pixel &pixel) {
	os << pixel.r << ' ' << pixel.g << ' ' << pixel.b;

	return os;
}

std::istream& operator>>(std::istream &is, Pixel &pixel) {
	is >> pixel.r >> pixel.g >> pixel.b;

	return is;
}

} // namespace octree

} // namespace eda
