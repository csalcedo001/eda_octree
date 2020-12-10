#include <iostream>

#include "image_3d.hpp"
#include "pixel.hpp"
#include "scan_octree.hpp"

using namespace std;

int main() {
	eda::octree::ScanOctree s(10, 10, 10);

	s.insert(5, 5, 2, 0);
	s.insert(2, 0, 5, 255);
	s.insert(4, 9, 0, 0);
	s.insert(8, 7, 3, 0);
	s.insert(7, 6, 8, 255);

	eda::octree::Image3D image(s);

	// cout << "Print image" << endl;
	// image.print();
	// cout << "Print quad tree" << endl;
	// s.print();
	// cout << "Print quad tree grid" << endl;
	// s.print_grid();

	image.set_cell(1, 8, 4, 255);

	eda::octree::ScanOctree s2(image, 1);


	// cout << "Print image" << endl;
	// image.print();
	// cout << "Print quad tree" << endl;
	// s2.print();
	// cout << "Print quad tree grid" << endl;
	// s2.print_grid();
	
	return 0;
}
