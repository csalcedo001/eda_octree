#include <iostream>

#include "octree.hpp"

using namespace std;

int main() {
	eda::octree::Octree<string> octree;

	int n;

	cin >> n;

	int x, y, z;
	string name;

	while (n--) {
		cin >> x >> y >> z >> name;

		octree.insert(x, y, z, name);
	}

	octree.print();

	return 0;
}
