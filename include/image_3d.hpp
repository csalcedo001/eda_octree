#ifndef OCTREE_IMAGE_HPP_
#define OCTREE_IMAGE_HPP_

#include <vector>

namespace eda {

namespace octree {

class Image3D;

} // namespace octree

} // namespace eda

#include "base_image_octree.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

class Image3D {
public:
	friend BaseImageOctree;

protected:
	int width_;
	int height_;
	int depth_;
	std::vector<std::vector<std::vector<Pixel> > > grid_;

public:
	Image3D(const Image3D &);
	Image3D(int, int, int);
	Image3D(BaseImageOctree &);

	int width();
	int height();
	int depth();
	std::vector<std::vector<std::vector<Pixel> > > &grid();
	void set_cell(int, int, int, Pixel);
	void print();
};

} // namespace octree

} // namespace eda

#endif // OCTREE_IMAGE_HPP_
