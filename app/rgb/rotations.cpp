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

	double angle[3];
	int side = (width + height) / 2; // Number of pixels in result image
	double z_scaling_factor = 10;

	int axis, rotations;

	cin >> axis >> rotations;

	angle[0] = angle[1] = angle[2] = 0;

	for (int rotation = 0; rotation < rotations; rotation++) {
		angle[axis] = 360. * rotation / rotations;

		auto slice = model.slice(angle[0], angle[1], angle[2], 0, side, z_scaling_factor);
		auto img = get_image_from_matrix(slice.grid());

		string filename = "data/rotation/result_" + to_string(rotation) + ".BMP";
		img.save_bmp(filename.c_str());
	}

	return 0;
}
