#ifndef OCTREE_BASE_IMAGE_3D_HPP_
#define OCTREE_BASE_IMAGE_3D_HPP_

#include "pixel.hpp"
#include "vector.hpp"
#include "image_2d.hpp"

namespace eda {

namespace octree {

class BaseImage3D {
protected:
	int width_;
	int height_;
	int depth_;

public:
	BaseImage3D(int, int, int);

	int width();
	int height();
	int depth();
	
	Image2D slice(double, double, double, double, int, double);

public:
	virtual Pixel color_at(int, int, int) = 0;
	virtual Pixel color_at(Vector) = 0;
};

} // namespace octree

} // namespace eda

#endif // OCTREE_BASE_IMAGE_3D_HPP_
