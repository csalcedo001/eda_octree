#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <random>

#include "scan_octree.hpp"
#include "image_3d.hpp"
#include "image_2d.hpp"
#include "vector.hpp"
#include "vectorize.h"

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

	auto begin = chrono::steady_clock::now();
	auto end = begin;

	double total_time = 0;
	int queries;

	cin >> queries;

	double angle_x, angle_y, angle_z, cut_depth;
	int side = eda::octree::Vector(width, height, depth).length();
	double z_scaling_factor = 10;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(0, 1);

	for (int i = 0; i < queries; i++) {
		angle_x = 360 * distribution(generator);
		angle_y = 360 * distribution(generator);
		angle_z = 360 * distribution(generator);
		cut_depth = side * distribution(generator) - side / 2.;

		begin = chrono::steady_clock::now();
		model->slice(angle_x, angle_y, angle_z, cut_depth, side, z_scaling_factor);
		end = chrono::steady_clock::now();

		total_time += chrono::duration_cast<chrono::microseconds>(end - begin).count();
	}

	structure_name[0] += 'A' - 'a';
	
	cout << structure_name << ':' << endl;
	cout << " - Total execution time: " << total_time  / 1000. << " ms" << endl;
	cout << " - Average execution time: " << total_time / queries / 1000. << " ms" << endl;

	return 0;
}
