#include <iostream>

#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main() {
	int width, height, depth;

	cin >> width >> height >> depth;

	eda::octree::Image3D image(width, height, depth);

	char c;

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				cin >> c;

				image.set_cell(x, y, z, eda::octree::Pixel((c - '0') * 255));
			}
		}
	}

	double threshold = 1;
	eda::octree::ScanOctree scan_octree(image, threshold);

	eda::octree::Image3D reconstructed_image(scan_octree);

	cout << "Input image:" << endl;
	image.print();

	cout << "Reconstructed image:" << endl;
	reconstructed_image.print();

	return 0;
}
