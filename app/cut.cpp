#include <iostream>
#include <fstream>

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

				model.set_cell(x, y, z, eda::octree::Pixel((c - '0') * 255));
			}
		}
	}

	double x_angle, y_angle, z_angle; // Sexagesimal
	double slice; // in [0, 1]
	double side; // Number of pixels in result image

	cin >> x_angle >> y_angle >> z_angle >> slice >> side;

	// Cube inscribed in sphere
	double radius = eda::octree::Vector(width, height, depth).length() / 2.;

	// Initially facing towards z axis
	double corner = radius / 2.;
	eda::octree::Vector origin(-corner, -corner, 0);
	eda::octree::Vector left_down_dir(-corner, corner, 0), top_right_dir(corner, -corner, 0);

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

	for (int y = 0; y < side; y++) {
		for (int x = 0; x < side; x++) {
			eda::octree::Vector dir_x = top_right_dir - origin;
			eda::octree::Vector dir_y = left_down_dir - origin;

			result[y][x] = model.color_at(
				dir_x * x / (side - 1) +
				dir_y * y / (side - 1) +
				origin
			);
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
