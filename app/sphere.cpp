#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int radius;

	cin >> radius;

	int edge = 2 * radius + 1;

	cout << edge << ' ' << edge << ' ' << edge << endl;

	for (int z = -radius; z <= radius; z++) {
		for (int y = -radius; y <= radius; y++) {
			for (int x = -radius; x <= radius; x++) {
				cout << (sqrt(x * x + y * y + z * z) <= radius ? 1 : 0);
			}
			cout << endl;
		}
	}

	return 0;
}
