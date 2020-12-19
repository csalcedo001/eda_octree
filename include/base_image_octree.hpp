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
#include "base_image_3d.hpp"
#include "node.hpp"
#include "pixel.hpp"
#include "vector.hpp"

namespace eda {

namespace octree {

class BaseImageOctree :
	public BaseOctree<Pixel, Node<Pixel> >,
	public BaseImage3D
{
public:
	friend Image3D;

public:
	BaseImageOctree(int, int, int);
	BaseImageOctree(Image3D &);

	Pixel color_at(int, int, int) override;
	Pixel color_at(Vector) override;

protected:
	Pixel color_at(Node<Pixel> *, int, int, int);

	void save_header(std::ostream &) override;
	void load_header(std::istream &) override;

public:
	virtual void fill(Image3D &) = 0;
};

} // namespace octree

} // namespace eda

// #include "impl/base_image_octree.ipp"

#endif // OCTREE_BASE_IMAGE_OCTREE_HPP_
