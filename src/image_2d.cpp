#include "image_2d.hpp"

#include <vector>

#include "base_image_octree.hpp"
#include "pixel.hpp"

namespace eda {

namespace octree {

Image2D::Image2D(const Image2D &image) : 
	width_(image.width_),
	height_(image.height_),
	grid_(image.grid_)
{ }

Image2D::Image2D(int width, int height) :
	width_(width),
	height_(height),
	grid_(height, std::vector<Pixel>(width))
{ }

int Image2D::width() {
	return this->width_;
}

int Image2D::height() {
	return this->height_;
}

std::vector<std::vector<Pixel> > &Image2D::grid() {
	return this->grid_;
}

Pixel &Image2D::cell(int x, int y) {
	return this->grid_[y][x];
}

void Image2D::print(double threshold) {
	for (auto row : this->grid_) {
		for (auto pixel : row) {
			std::cout << ((pixel.r + pixel.g + pixel.b) / 3. < threshold ? '.' : 'X');
		}
		std::cout << std::endl;
	}
}

} // namespace octree

} // namespace eda
