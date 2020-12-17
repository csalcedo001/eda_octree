#ifndef OCTREE_IMAGE_3D_HPP_
#define OCTREE_IMAGE_3D_HPP_

#include <vector>

namespace eda {

namespace octree {

class Image3D;

} // namespace octree

} // namespace eda

#include "base_image_octree.hpp"
#include "pixel.hpp"
#include "vector.hpp"

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
	Pixel &cell(int, int, int);
	void print();

	Pixel color_at(int, int, int);
	Pixel color_at(Vector);
};

} // namespace octree

} // namespace eda

#endif // OCTREE_IMAGE_3D_HPP_
