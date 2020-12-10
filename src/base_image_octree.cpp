#include "base_image_octree.hpp"

#include <vector>

#include "base_octree.hpp"
#include "image_3d.hpp"
#include "node.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

BaseImageOctree::BaseImageOctree(int width, int height, int depth) :
	BaseOctree<Pixel, Node<Pixel> >(),
	width_(width),
	height_(height),
	depth_(depth)
{ }

BaseImageOctree::BaseImageOctree(Image3D &image) :
	BaseOctree<Pixel, Node<Pixel> >(),
	width_(image.width_),
	height_(image.height_),
	depth_(image.depth_)
{ }

int BaseImageOctree::width() {
	return this->width_;
}

int BaseImageOctree::height() {
	return this->height_;
}

int BaseImageOctree::depth() {
	return this->depth_;
}

// void BaseImageOctree::print_grid() {
// 	std::vector<std::vector<bool> > grid(this->height_, std::vector<bool>(this->width_, false));
// 
// 	this->print_grid(this->head_, grid);
// 
// 	for (auto row : grid) {
// 		for (auto cell : row) {
// 			std::cout << (cell ? 'X' : '.');
// 		}
// 		std::cout << std::endl;
// 	}
// }
// 
// void BaseImageOctree::print_grid(Node<Pixel> *node, std::vector<std::vector<bool> > &grid) {
// 	if (node != nullptr) {
// 		this->print_grid(node->children_[0], grid);
// 		this->print_grid(node->children_[1], grid);
// 
// 		grid[node->y_][node->x_] = true;
// 
// 		this->print_grid(node->children_[2], grid);
// 		this->print_grid(node->children_[3], grid);
// 	}
// }

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
