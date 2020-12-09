#include <iostream>
#include <fstream>
#include <sstream>

#include "image_3d.hpp"
#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 3) {
		cerr << "error: missing arguments. Usage: " << argv[0] << " <output_path> <threshold>" << endl;
		return 1;
	}

	string output_path(argv[1]);
	fstream output_file(output_path, ios::binary | ios::out);

	if (!output_file.is_open()) {
		cerr << "error: unable to open " << argv[1] << endl;
		return 1;
	}

	stringstream ss(argv[2]);
	int threshold;

	ss >> threshold;


	int width, height;

	cin >> width >> height;

	eda::octree::Image3D image(width, height);

	eda::octree::Pixel pixel;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cin >> pixel;

			image.set_cell(j, i, pixel);
		}
	}

	eda::octree::ScanOctree octree(image, threshold);

	octree.save(output_file);

	return 0;
}
