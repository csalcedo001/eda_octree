#include "image_3d.hpp"

#include <vector>

#include "base_image_octree.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

Image3D::Image3D(const Image3D &image) : 
	width_(image.width_),
	height_(image.height_),
	depth_(image.depth_),
	grid_(image.grid_)
{ }

Image3D::Image3D(int width, int height, int depth) :
	width_(width),
	height_(height),
	depth_(depth),
	grid_(depth, std::vector<std::vector<Pixel> >(height, std::vector<Pixel>(width)))
{ }

Image3D::Image3D(BaseImageOctree &tree) :
	width_(tree.width_),
	height_(tree.height_),
	depth_(tree.depth_),
	grid_(tree.depth_, std::vector<std::vector<Pixel> >(tree.height_, std::vector<Pixel>(tree.width_)))
{
	tree.fill(*this);
}

int Image3D::width() {
	return this->width_;
}

int Image3D::height() {
	return this->height_;
}

int Image3D::depth() {
	return this->depth_;
}

std::vector<std::vector<std::vector<Pixel> > > &Image3D::grid() {
	return this->grid_;
}

void Image3D::set_cell(int x, int y, int z, Pixel pixel) {
	this->grid_[z][y][x] = pixel;
}

void Image3D::print() {
	for (auto matrix : this->grid_) {
		for (auto row : matrix) {
			for (auto pixel : row) {
				std::cout << (pixel.r + pixel.g + pixel.b < 3 * 128 ? '.' : 'X');
			}
			std::cout << std::endl;
		}
	}
}

} // namespace octree

} // namespace eda
