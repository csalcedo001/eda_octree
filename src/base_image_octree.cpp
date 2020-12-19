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

	if (this->head_ == nullptr) return Pixel();

	return this->color_at(this->head_, x, y, z);
}

Pixel BaseImageOctree::color_at(Vector v) {
	return this->color_at(v.x, v.y, v.z);
}

Pixel BaseImageOctree::color_at(Node<Pixel> *node, int x, int y, int z) {
	bool right_side = x > node->x_;
	bool down_side = y > node->y_;
	bool back_side = z > node->z_;

	int index = (back_side << 2) + (down_side << 1) + right_side;

	if (node->children_[index] == nullptr) return node->data_;

	return this->color_at(node->children_[index], x, y, z);
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
