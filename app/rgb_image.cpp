#include <iostream>

#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main() {
	int width, height;

	cin >> width >> height;

	eda::octree::Image image(width, height);

	int c;

	eda::octree::Pixel pixel;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cin >> pixel;

			image.set_cell(j, i, pixel);
		}
	}

	eda::octree::ScanOctree scan_octree(image, 1);

	eda::octree::Image reconstructed_image(scan_octree);

	cout << "Input image:" << endl;
	image.print();

	cout << "Compressed quad tree grid:" << endl;
	scan_octree.print_grid();

	cout << "Reconstructed image:" << endl;
	reconstructed_image.print();

	return 0;
}
