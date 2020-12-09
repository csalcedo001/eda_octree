#include <iostream>

#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main() {
	int n;

	cin >> n;

	eda::octree::Image3D image(n, n);

	int c;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> c;

			image.set_cell(j, i, eda::octree::Pixel(c * 255));
		}
	}

	eda::octree::ScanOctree scan_octree(image, 1);

	eda::octree::Image3D reconstructed_image(scan_octree);

	cout << "Input image:" << endl;
	image.print();

	cout << "Compressed quad tree grid:" << endl;
	scan_octree.print_grid();

	cout << "Reconstructed image:" << endl;
	reconstructed_image.print();

	return 0;
}
