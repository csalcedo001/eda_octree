#ifndef OCTREE_SCAN_OCTREE_HPP_
#define OCTREE_SCAN_OCTREE_HPP_

#include "base_image_octree.hpp"
#include "node.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

class ScanOctree : public BaseImageOctree {
public:
	ScanOctree(int, int, double);
	ScanOctree(Image &, double);
	void fill(Image &);

private:
	void build(Node<Pixel> *&, Image &, int, int, int, int);
	bool same_color(Image &, int, int, int, int);
	Pixel average_pixel(Image &, int, int, int, int);
	void fill(Node<Pixel> *, Image &, int, int, int, int);
};

} // namespace octree

} // namespace eda

#endif // OCTREE_SCAN_OCTREE_HPP_
