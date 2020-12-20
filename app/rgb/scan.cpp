#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "image_3d.hpp"
#include "image_2d.hpp"
#include "vector.hpp"
#include "vectorize.h"
#include "scan_octree.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 3) {
		cerr << "error: missing arguments. Usage:" << argv[0] << " <input_directory> <structure>" << endl;
		return 1;
	}

	string directory_name(argv[1]);

	auto raw_image = eda::octree::get_vectors_from_mri(directory_name, "Paciente1CC-27-10-1988- CT from 18-01-2011 S0 I", 39, 40);

	int width, height, depth;

	width = raw_image[0][0].size();
	height = raw_image[0].size();
	depth = raw_image.size();

	eda::octree::Image3D *image = new eda::octree::Image3D(width, height, depth);

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				image->cell(x, y, z) = raw_image[z][y][x];
			}
		}
	}


	eda::octree::BaseImage3D *model;
	string structure_name(argv[2]);

	if (structure_name == "grid") {
		model = image;
	}
	else if (structure_name == "octree") {
		double threshold;

		cin >> threshold;

		model = new eda::octree::ScanOctree(*image, threshold);

		delete image;
	}
	else {
		cerr << "error: unsupported structure '" << structure_name << "'. Supported structures are 'grid' and 'octree'." << endl;
		return 1;
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

		auto slice = model->slice(x_angle, y_angle, z_angle, cut_depth, side, z_scaling_factor);
		auto img = get_image_from_matrix(slice.grid());

		stringstream ss;

		ss << setw(3) << setfill('0') << cut;

		string index = ss.str();

		string filename = "data/scan/result_" + index + ".BMP";
		img.save_bmp(filename.c_str());
	}

	return 0;
}
