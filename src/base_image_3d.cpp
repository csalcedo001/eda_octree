#include "base_image_3d.hpp"

#include "pixel.hpp"
#include "vector.hpp"

namespace eda {

namespace octree {

BaseImage3D::BaseImage3D(int width, int height, int depth) :
	width_(width),
	height_(height),
	depth_(depth)
{ }

int BaseImage3D::width() {
	return this->width_;
}

int BaseImage3D::height() {
	return this->height_;
}

int BaseImage3D::depth() {
	return this->depth_;
}

Image2D BaseImage3D::slice(double x_angle, double y_angle, double z_angle, double cut_depth, int image_size, double z_scaling_factor) {
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
