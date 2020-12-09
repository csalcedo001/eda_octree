#include <iostream>

#include "octree.hpp"

using namespace std;

int main() {
	eda::octree::Octree<string> octree;

	int n;

	cin >> n;

	int x, y;
	string name;

	while (n--) {
		cin >> x >> y >> name;

		octree.insert(x, y, name);
	}

	octree.print();

	return 0;
}
