#ifndef OCTREE_PIXEL_HPP_
#define OCTREE_PIXEL_HPP_

#include <fstream>

namespace eda {

namespace octree {

struct Pixel {
	int r;
	int g;
	int b;

	Pixel(const Pixel &);
	Pixel(int, int, int);
	Pixel(int = 0);

	double average();

	friend std::ostream& operator<<(std::ostream &, const Pixel &);
	friend std::istream& operator>>(std::istream &, Pixel &);
};

} // namespace octree

} // namespace eda

#endif // OCTREE_PIXEL_HPP_
