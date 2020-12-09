#include "image_3d.hpp"

#include <vector>

#include "base_image_octree.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

Image3D::Image3D(const Image3D &image) : 
	width_(image.width_),
	height_(image.height_),
	grid_(image.grid_)
{ }

Image3D::Image3D(int width, int height) :
	width_(width),
	height_(height),
	grid_(height, std::vector<Pixel>(width))
{ }

Image3D::Image3D(BaseImageOctree &tree) :
	width_(tree.width_),
	height_(tree.height_),
	grid_(tree.height_, std::vector<Pixel>(tree.width_))
{
	tree.fill(*this);
}

int Image3D::width() {
	return this->width_;
}

int Image3D::height() {
	return this->height_;
}

std::vector<std::vector<Pixel> > &Image3D::grid() {
	return this->grid_;
}

void Image3D::set_cell(int x, int y, Pixel pixel) {
	this->grid_[y][x] = pixel;
}

void Image3D::print() {
	for (auto row : this->grid_) {
		for (auto pixel : row) {
			std::cout << (pixel.r + pixel.g + pixel.b < 3 * 128 ? '.' : 'X');
		}
		std::cout << std::endl;
	}
}

} // namespace octree

} // namespace eda
