#ifndef OCTREE_BASE_IMAGE_OCTREE_HPP_
#define OCTREE_BASE_IMAGE_OCTREE_HPP_

#include <vector>
#include <fstream>

namespace eda {

namespace octree {

class BaseImageOctree;

} // namespace octree

} // namespace eda

#include "base_octree.hpp"
#include "image_3d.hpp"
#include "node.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

class BaseImageOctree : public BaseOctree<Pixel, Node<Pixel> > {
public:
	friend Image3D;

protected:
	int width_;
	int height_;
	int depth_;
	double threshold_;

public:
	BaseImageOctree(int, int, int, double);
	BaseImageOctree(Image3D &, double);

	// void print_grid();
	int width();
	int height();
	int depth();

protected:
	// void print_grid(Node<Pixel> *, std::vector<std::vector<bool> > &);

public:
	virtual void fill(Image3D &) = 0;

protected:
	void save_header(std::ostream &);
	void load_header(std::istream &);
};

} // namespace octree

} // namespace eda

// #include "impl/base_image_octree.ipp"

#endif // OCTREE_BASE_IMAGE_OCTREE_HPP_
