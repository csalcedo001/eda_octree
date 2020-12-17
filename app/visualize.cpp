#include <iostream>

#include "scan_octree.hpp"
#include "pixel.hpp"

using namespace std;

int main() {
	int width, height, depth;

	cin >> width >> height >> depth;

	eda::octree::Image3D image(width, height, depth);

	int c;

	eda::octree::Pixel pixel;

	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				cin >> pixel;

				image.cell(x, y, z) = pixel;
			}
		}
	}

	image.print();

	return 0;
}
