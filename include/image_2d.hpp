#ifndef OCTREE_IMAGE_2D_HPP_
#define OCTREE_IMAGE_2D_HPP_

#include <vector>

#include "pixel.hpp"

namespace eda {

namespace octree {

class Image2D {
protected:
	int width_;
	int height_;
	std::vector<std::vector<Pixel> > grid_;

public:
	Image2D(const Image2D &);
	Image2D(int, int);

	int width();
	int height();
	std::vector<std::vector<Pixel> > &grid();
	Pixel &cell(int, int);
	void print(double = 128);
};

} // namespace octree

} // namespace eda

#endif // OCTREE_IMAGE_2D_HPP_
