#include "base_image_octree.hpp"

#include <vector>

#include "base_octree.hpp"
#include "image_3d.hpp"
#include "base_image_3d.hpp"
#include "node.hpp"
#include "pixel.hpp"
#include "vector.hpp"

namespace eda {

namespace octree {

BaseImageOctree::BaseImageOctree(int width, int height, int depth) :
	BaseOctree<Pixel, Node<Pixel> >(),
	BaseImage3D(width, height, depth)
{ }

BaseImageOctree::BaseImageOctree(Image3D &image) :
	BaseOctree<Pixel, Node<Pixel> >(),
	BaseImage3D(image.width_, image.height_, image.depth_)
{ }

Pixel BaseImageOctree::color_at(int x, int y, int z) {
	if (x < 0 || x >= this->width_) return Pixel();
	if (y < 0 || y >= this->height_) return Pixel();
	if (z < 0 || z >= this->depth_) return Pixel();

	return this->color_at(this->head_, x, y, z);
}

Pixel BaseImageOctree::color_at(Vector v) {
	return this->color_at(v.x, v.y, v.z);
}

Pixel BaseImageOctree::color_at(Node<Pixel> *node, int x, int y, int z) {
	// TODO: Implement recursive call to find color

	return Pixel();
}

void BaseImageOctree::save_header(std::ostream &os) {
	os.write((char *) &this->width_, sizeof(int));
	os.write((char *) &this->height_, sizeof(int));
	os.write((char *) &this->depth_, sizeof(int));
}

void BaseImageOctree::load_header(std::istream &is) {
	is.read((char *) &this->width_, sizeof(int));
	is.read((char *) &this->height_, sizeof(int));
	is.read((char *) &this->depth_, sizeof(int));
}

} // namespace octree

} // namespace eda
