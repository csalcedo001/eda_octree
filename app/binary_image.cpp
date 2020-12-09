#include <iostream>

#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main() {
	int n;

	cin >> n;

	eda::octree::Image3D image(n, n, n);

	int c;

	for (int z = 0; z < n; z++) {
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				cin >> c;

				image.set_cell(x, y, z, eda::octree::Pixel(c * 255));
			}
		}
	}

	eda::octree::ScanOctree scan_octree(image, 1);

	eda::octree::Image3D reconstructed_image(scan_octree);

	cout << "Input image:" << endl;
	image.print();

	// cout << "Compressed quad tree grid:" << endl;
	// scan_octree.print_grid();

	cout << "Reconstructed image:" << endl;
	reconstructed_image.print();

	return 0;
}
