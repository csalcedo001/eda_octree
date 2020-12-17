#include <iostream>
#include <fstream>
#include <cmath>

#include "image_3d.hpp"
#include "vector.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "error: missing argument 'input_file'. Usage:" << argv[0] << " <input_file>" << endl;
		return 1;
	}

	string filename(argv[1]);
	fstream input_file(filename, ios::in);

	if (!input_file.is_open()) {
		cerr << "error: unable to open " << filename << endl;
		return 1;
	}

	int width, height, depth;

	input_file >> width >> height >> depth;

	eda::octree::Image3D model(width, height, depth);

	char c;

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				input_file >> c;

				model.cell(x, y, z) = (c - '0') * 255;
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

	cout << origin.x << ' ' << origin.y << ' ' << origin.z << endl;
	cout << left_down_dir.x << ' ' << left_down_dir.y << ' ' << left_down_dir.z << endl;
	cout << top_right_dir.x << ' ' << top_right_dir.y << ' ' << top_right_dir.z << endl;

	cout << "..." << endl;

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

	cout << origin.x << ' ' << origin.y << ' ' << origin.z << endl;
	cout << left_down_dir.x << ' ' << left_down_dir.y << ' ' << left_down_dir.z << endl;
	cout << top_right_dir.x << ' ' << top_right_dir.y << ' ' << top_right_dir.z << endl;

	cout << "..." << endl;

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
