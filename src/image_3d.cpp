#include "image_3d.hpp"

#include <vector>

#include "base_image_octree.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

Image::Image(const Image &image) : 
	width_(image.width_),
	height_(image.height_),
	grid_(image.grid_)
{ }

Image::Image(int width, int height) :
	width_(width),
	height_(height),
	grid_(height, std::vector<Pixel>(width))
{ }

Image::Image(BaseImageOctree &tree) :
	width_(tree.width_),
	height_(tree.height_),
	grid_(tree.height_, std::vector<Pixel>(tree.width_))
{
	tree.fill(*this);
}

int Image::width() {
	return this->width_;
}

int Image::height() {
	return this->height_;
}

std::vector<std::vector<Pixel> > &Image::grid() {
	return this->grid_;
}

void Image::set_cell(int x, int y, Pixel pixel) {
	this->grid_[y][x] = pixel;
}

void Image::print() {
	for (auto row : this->grid_) {
		for (auto pixel : row) {
			std::cout << (pixel.r + pixel.g + pixel.b < 3 * 128 ? '.' : 'X');
		}
		std::cout << std::endl;
	}
}

} // namespace octree

} // namespace eda
