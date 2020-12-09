#include <iostream>
#include <fstream>
#include <sstream>

#include "image_3d.hpp"
#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 3) {
		cerr << "error: missing argument. Usage: " << argv[0] << " <octree_path> <image_path>" << endl;
		return 1;
	}

	string octree_path(argv[1]);
	fstream octree_file(octree_path, ios::binary | ios::in);

	if (!octree_file.is_open()) {
		cerr << "error: unable to open " << argv[1] << endl;
		return 1;
	}

	string image_path(argv[2]);
	fstream image_file(image_path, ios::out);

	if (!image_file.is_open()) {
		cerr << "error: unable to open " << argv[2] << endl;
		return 1;
	}

	// TODO: update data loading to restore image width and height
	eda::octree::ScanOctree octree(0, 0, 0, 0);

	octree.load(octree_file);

	eda::octree::Image3D image(octree);

	image_file << image.width() << ' ' << image.height() << ' ' << image.depth() << endl;

	for (auto matrix : image.grid()) {
		for (auto row : matrix) {
			for (auto pixel : row) {
				image_file << pixel << endl;
			}
		}
	}

	return 0;
}
