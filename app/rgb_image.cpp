#include <iostream>

#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main() {
	int width, height, depth;

	cin >> width >> height;

	eda::octree::Image3D image(width, height, depth);

	int c;

	eda::octree::Pixel pixel;

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				cin >> pixel;

				image.set_cell(x, y, z, pixel);
			}
		}
	}

	eda::octree::ScanOctree scan_octree(image, 1);

	eda::octree::Image3D reconstructed_image(scan_octree);

	// cout << "Input image:" << endl;
	// image.print();

	// cout << "Compressed quad tree grid:" << endl;
	// scan_octree.print_grid();

	// cout << "Reconstructed image:" << endl;
	// reconstructed_image.print();

	return 0;
}
