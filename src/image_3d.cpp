#include "image_3d.hpp"

#include <vector>
#include <cmath>

#include "base_image_octree.hpp"
#include "pixel.hpp"
#include "image_2d.hpp"

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
	return this->grid_[z][y][x];
}

Pixel Image3D::color_at(Vector v) {
	if (v.x < 0 || v.x >= this->width_) return Pixel();
	if (v.y < 0 || v.y >= this->height_) return Pixel();
	if (v.z < 0 || v.z >= this->depth_) return Pixel();

	return this->grid_[v.z][v.y][v.x];
}

Image2D Image3D::slice(double x_angle, double y_angle, double z_angle, double cut_depth, int image_size, double z_scaling_factor) {
	// Set angle unit from sexagesimal to radians
	x_angle *= 3.1416 / 180;
	y_angle *= 3.1416 / 180;
	z_angle *= 3.1416 / 180;

	// Cube inscribed in sphere
	double radius = eda::octree::Vector(this->width_, this->height_, this->depth_).length() / 2.;

	// Initialize image corners facing towards z axis
	double corner = radius;
	eda::octree::Vector top_left(-corner, corner, -cut_depth);
	eda::octree::Vector bottom_left(-corner, -corner, -cut_depth);
	eda::octree::Vector top_right(corner, corner, -cut_depth);

	// Perform rotations over image corners
	top_left.rotate_z(-z_angle);
	bottom_left.rotate_z(-z_angle);
	top_right.rotate_z(-z_angle);

	top_left.rotate_y(-y_angle);
	bottom_left.rotate_y(-y_angle);
	top_right.rotate_y(-y_angle);

	top_left.rotate_x(x_angle);
	bottom_left.rotate_x(x_angle);
	top_right.rotate_x(x_angle);

	// Invert y and z axis
	top_left.y *= -1;
	bottom_left.y *= -1;
	top_right.y *= -1;

	top_left.z *= -1;
	bottom_left.z *= -1;
	top_right.z *= -1;

	// Create blank image to be filled
	eda::octree::Image2D slice(image_size, image_size);

	eda::octree::Vector sphere_center(this->width_ / 2., this->height_ / 2., this->depth_ / 2. * z_scaling_factor);
	eda::octree::Vector width_vector = top_right - top_left;
	eda::octree::Vector height_vector = bottom_left - top_left;

	// Fill slice with colors from model
	for (int y = 0; y < image_size; y++) {
		for (int x = 0; x < image_size; x++) {
			auto pixel_position = width_vector * x / (image_size - 1.) +
				height_vector * y / (image_size - 1.) +
				top_left + sphere_center;

			pixel_position.z /= z_scaling_factor;

			slice.cell(x, y) = this->color_at(pixel_position);
		}
	}

	return slice;
}

} // namespace octree

} // namespace eda
