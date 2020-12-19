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

	auto raw_image = eda::octree::get_vectors_from_mri(directory_name, "Paciente1CC-27-10-1988- CT from 18-01-2011 S0 I", 39, 40);

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

	double x_angle, y_angle, z_angle;
	int side = (width + height) / 2; // Number of pixels in result image
	double z_scaling_factor = 10;
	double cuts;

	cin >> x_angle >> y_angle >> z_angle >> cuts;

	double cut_depth;
	double radius = eda::octree::Vector(width, height, depth).length() / 2.;

	for (double cut = 0; cut <= cuts; cut++) {
		cut_depth = 2 * radius * cut / cuts - radius;

		auto slice = model.slice(x_angle, y_angle, z_angle, cut_depth, side, z_scaling_factor);
		auto img = get_image_from_matrix(slice.grid());

		string filename = "data/scan/result_" + to_string((int) cut) + ".BMP";
		img.save_bmp(filename.c_str());
	}

	return 0;
}
