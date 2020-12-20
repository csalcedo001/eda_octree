#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <random>
#include <sstream>

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

	// Load raw images
	string directory_name(argv[1]);

	auto raw_image = eda::octree::get_vectors_from_mri(directory_name, "Paciente1CC-27-10-1988- CT from 18-01-2011 S0 I", 39, 40);

	int width, height, depth;

	width = raw_image[0][0].size();
	height = raw_image[0].size();
	depth = raw_image.size();


	// Fill 3D image with pixels
	eda::octree::Image3D *image = new eda::octree::Image3D(width, height, depth);

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				image->cell(x, y, z) = raw_image[z][y][x];
			}
		}
	}


	// Validate and setup 3D image representation
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

	// Setup slicing variables
	int queries;

	cin >> queries;

	double angle_x, angle_y, angle_z, cut_depth;
	double side = eda::octree::Vector(width, height, depth).length();
	double random_cut_depth_range = side / sqrt(2) * 0.8;
	double z_scaling_factor = 10;

	// Setup time execution time measurement variables
	double total_time = 0;

	auto begin = chrono::steady_clock::now();
	auto end = begin;

	// Setup random engine and distribution
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(0, 1);

	for (int query = 0; query < queries; query++) {
		// Generate random slice
		angle_x = 360. * distribution(generator);
		angle_y = 360. * distribution(generator);
		angle_z = 360. * distribution(generator);
		cut_depth = random_cut_depth_range * (distribution(generator) - 0.5);


		// Measure execution time of slicing
		begin = chrono::steady_clock::now();
		auto slice = model->slice(angle_x, angle_y, angle_z, cut_depth, side, z_scaling_factor);
		end = chrono::steady_clock::now();

		total_time += chrono::duration_cast<chrono::microseconds>(end - begin).count();


		// Save slices in data/random
		auto img = get_image_from_matrix(slice.grid());

		stringstream ss;

		ss << setw(4) << setfill('0') << query;

		string index = ss.str();

		string filename = "data/random/result_" + index + ".BMP";
		img.save_bmp(filename.c_str());
	}

	// Output total execution time and average slice execution time
	structure_name[0] += 'A' - 'a';
	
	cout << structure_name << ':' << endl;
	cout << " - Total execution time: " << total_time  / 1000. << " ms" << endl;
	cout << " - Average execution time: " << total_time / queries / 1000. << " ms" << endl;

	return 0;
}
