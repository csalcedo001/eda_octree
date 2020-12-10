#ifndef OCTREE_SCAN_OCTREE_HPP_
#define OCTREE_SCAN_OCTREE_HPP_

#include "base_image_octree.hpp"
#include "node.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

class ScanOctree : public BaseImageOctree {
public:
	ScanOctree(int, int, int);
	ScanOctree(Image3D &, double);
	void fill(Image3D &);

private:
	void build(Node<Pixel> *&, Image3D &, double, int, int, int, int, int, int);
	bool same_color(Image3D &, double, int, int, int, int, int, int);
	Pixel average_pixel(Image3D &, int, int, int, int, int, int);
	void fill(Node<Pixel> *, Image3D &, int, int, int, int, int, int);
};

} // namespace octree

} // namespace eda

#endif // OCTREE_SCAN_OCTREE_HPP_
