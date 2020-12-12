#include <iostream>
#include <fstream>
#include <cmath>

#include "image_3d.hpp"
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

	int c;

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				c = raw_image[z][y][x];

				model.set_cell(x, y, z, eda::octree::Pixel(c));
			}
		}
	}

	double x_angle, y_angle, z_angle; // Sexagesimal
	double slice; // in [0, 1]
	double side; // Number of pixels in result image

	cin >> x_angle >> y_angle >> z_angle >> slice >> side;

	x_angle *= 3.1416 / 180;
	y_angle *= 3.1416 / 180;
	z_angle *= 3.1416 / 180;

	// Cube inscribed in sphere
	double radius = eda::octree::Vector(width, height, depth).length() / 2.;

	// Initially facing towards z axis
	double corner = sqrt(2) * radius / 2.;
	eda::octree::Vector origin(-corner, corner, 0);
	eda::octree::Vector left_down_dir(-corner, -corner, 0), top_right_dir(corner, corner, 0);

	// Perform rotations
	origin.rotate_x(x_angle);
	left_down_dir.rotate_x(x_angle);
	top_right_dir.rotate_x(x_angle);

	origin.rotate_y(y_angle);
	left_down_dir.rotate_y(y_angle);
	top_right_dir.rotate_y(y_angle);

	origin.rotate_z(z_angle);
	left_down_dir.rotate_z(z_angle);
	top_right_dir.rotate_z(z_angle);

	origin.z += slice;
	left_down_dir.z += slice;
	top_right_dir.z += slice;

	vector<vector<eda::octree::Pixel> > result(side, vector<eda::octree::Pixel>(side));

	eda::octree::Vector sphere_center(width / 2., height / 2., depth / 2.);
	eda::octree::Vector dir_x = top_right_dir - origin;
	eda::octree::Vector dir_y = left_down_dir - origin;

	for (int y = 0; y < side; y++) {
		for (int x = 0; x < side; x++) {
			auto v = dir_x * (double) x / (side - 1.) +
				dir_y * (double) y / (side - 1.) +
				origin + sphere_center;

			// v.y *= -1;
			// v.z *= -1;

			result[y][x] = model.color_at(v);

			cout << v.x << ' ' << v.y << ' ' << v.z << ' ' << result[y][x] << endl;
		}
	}

	for (auto row : result) {
		for (auto pixel : row) {
			cout << (pixel.average() > 128 ? 1 : 0);
		}
		cout << endl;
	}

	return 0;
}
