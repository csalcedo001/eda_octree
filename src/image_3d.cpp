#include "image_3d.hpp"

#include <vector>
#include <cmath>

#include "base_image_octree.hpp"
#include "pixel.hpp"
#include "image_2d.hpp"
#include "image_3d.hpp"

namespace eda {

namespace octree {

Image3D::Image3D(const Image3D &image) : 
	BaseImage3D(image.width_, image.height_, image.depth_),
	grid_(image.grid_)
{ }

Image3D::Image3D(int width, int height, int depth) :
	BaseImage3D(width, height, depth),
	grid_(depth, std::vector<std::vector<Pixel> >(height, std::vector<Pixel>(width)))
{ }

Image3D::Image3D(BaseImageOctree &tree) :
	BaseImage3D(tree.width_, tree.height_, tree.depth_),
	grid_(tree.depth_, std::vector<std::vector<Pixel> >(tree.height_, std::vector<Pixel>(tree.width_)))
{
	tree.fill(*this);
}

std::vector<std::vector<std::vector<Pixel> > > &Image3D::grid() {
	return this->grid_;
}

Pixel &Image3D::cell(int x, int y, int z) {
	return this->grid_[z][y][x];
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

Pixel Image3D::color_at(int x, int y, int z) {
	if (x < 0 || x >= this->width_) return Pixel();
	if (y < 0 || y >= this->height_) return Pixel();
	if (z < 0 || z >= this->depth_) return Pixel();

	return this->grid_[z][y][x];
}

Pixel Image3D::color_at(Vector v) {
	return this->color_at(v.x, v.y, v.z);
}

size_t Image3D::getRAM() {
	return sizeof(this->grid_) + 3 * sizeof(int) + this->width_ * this->height_ * this->depth_ * sizeof(Pixel);
}

} // namespace octree

} // namespace eda
