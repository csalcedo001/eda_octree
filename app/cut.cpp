#include <iostream>

#include "image_3d.hpp"
#include "vector.hpp"

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

	// origin: Result image (0, 0) position on 3D space
	// seg_x: Image's left side as a vector pointing to left bottom corner of image on 3D space
	// seg_y: Image's top side as a vector pointing to right top corner of image on 3D space

	eda::octree::Vector origin(0, 5, 0), seg_x(10, 0, 0), seg_y(0, 0, 10);

	int result_width, result_height;

	// Image resolution
	result_width = 40;
	result_height = 20;

	vector<vector<eda::octree::Pixel> > result(result_height, vector<eda::octree::Pixel>(result_width));

	for (int y = 0; y < result_height; y++) {
		for (int x = 0; x < result_width; x++) {
			eda::octree::Vector dir_x = seg_x - origin;
			eda::octree::Vector dir_y = seg_y - origin;

			result[y][x] = image.color_at(
				dir_x * x / (result_width - 1) +
				dir_y * y / (result_height - 1) +
				origin
			);
		}
	}

	for (auto row : result) {
		for (auto pixel : row) {
			cout << (pixel.average() > 128 ? 1 : 0);
		}
		cout << endl;
	}

	return 0;
}
