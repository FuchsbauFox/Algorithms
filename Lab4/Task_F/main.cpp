#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("garland.in");
	ofstream fout("garland.out");
	int n;
	fin >> n;
	double h1;
	fin >> h1;
	double left = 0, right = h1, last = -1, mid, previous, current, next;
	bool ground;
	while (true) {
		mid = (left + right) / 2;
		if (mid == left || mid == right) {
			break;
		}
		previous = h1;
		current = mid;
		ground = true;
		for (int i = 2; i < n; i++) {
			next = 2 * current - previous + 2;
			ground &= next > 0;
			previous = current;
			current = next;
		}
		if (ground) {
			right = mid;
			last = current;
		}
		else {
			left = mid;
		}
	}
	fout.setf(ios::fixed);
	fout.precision(2);
	fout << last;
	fin.close();
	fout.close();
	return 0;
}