#include <iostream>
#include <fstream>
#include <cmath>

#include "image_3d.hpp"
#include "image_2d.hpp"
#include "vector.hpp"
#include "vectorize.h"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "error: missing argument 'input_directory'. Usage:" << argv[0] << " <input_directory>" << endl;
		return 1;
	}

	string directory_name(argv[1]);

	auto raw_image = get_vectors_from_mri(directory_name, "Paciente1CC-27-10-1988- CT from 18-01-2011 S0 I", 39, 40);

	int width, height, depth;

	width = raw_image[0][0].size();
	height = raw_image[0].size();
	depth = raw_image.size();

	eda::octree::Image3D model(width, height, depth);

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				model.cell(x, y, z) = raw_image[z][y][x];
			}
		}
	}

	double x_angle, y_angle, z_angle; // Sexagesimal
	double cut_depth; // in [0, 1]
	double side; // Number of pixels in result image
	double z_scaling_factor = 13;

	cin >> x_angle >> y_angle >> z_angle >> cut_depth >> side;

	x_angle *= 3.1416 / 180;
	y_angle *= 3.1416 / 180;
	z_angle *= 3.1416 / 180;

	// Cube inscribed in sphere
	double radius = eda::octree::Vector(width, height, depth).length() / 2.;

	// Initially facing towards z axis
	double corner = sqrt(2) * radius;
	eda::octree::Vector origin(-corner, corner, -cut_depth);
	eda::octree::Vector left_down_dir(-corner, -corner, -cut_depth);
	eda::octree::Vector top_right_dir(corner, corner, -cut_depth);

	// Perform rotations over image corners
	origin.rotate_z(-z_angle);
	left_down_dir.rotate_z(-z_angle);
	top_right_dir.rotate_z(-z_angle);

	origin.rotate_y(-y_angle);
	left_down_dir.rotate_y(-y_angle);
	top_right_dir.rotate_y(-y_angle);

	origin.rotate_x(x_angle);
	left_down_dir.rotate_x(x_angle);
	top_right_dir.rotate_x(x_angle);

	// Invert y and z axis
	origin.y *= -1;
	left_down_dir.y *= -1;
	top_right_dir.y *= -1;

	origin.z *= -1;
	left_down_dir.z *= -1;
	top_right_dir.z *= -1;

	// Create blank image to be filled
	eda::octree::Image2D slice(side, side);

	eda::octree::Vector sphere_center(width / 2., height / 2., depth / 2.);
	eda::octree::Vector width_vector = top_right_dir - origin;
	eda::octree::Vector height_vector = left_down_dir - origin;

	// Fill slice with colors from model
	for (int y = 0; y < side; y++) {
		for (int x = 0; x < side; x++) {
			auto pixel_position = width_vector * x / (side - 1.) +
				height_vector * y / (side - 1.) +
				origin + sphere_center;

			pixel_position.z /= z_scaling_factor;

			slice.cell(x, y) = model.color_at(pixel_position);
		}
	}

	double threshold = 180;
	slice.print(threshold);

	return 0;
}
