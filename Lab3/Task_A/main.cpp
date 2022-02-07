#include <iostream>
#include <fstream>

using namespace std;

int main() {
	int n, i;
	ifstream fin("isheap.in");
	ofstream fout("isheap.out");
	fin >> n;
	int* arr = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		fin >> arr[i];
	}
	for (i = 1; i <= n / 2; i++) {
		if (2 * i <= n && arr[i] > arr[2 * i]) {
			break;
		}
		if (2 * i + 1 <= n && arr[i] > arr[2 * i + 1]) {
			break;
		}
	}
	i <= n / 2 ? fout << "NO" : fout << "YES";
	fin.close();
	fout.close();
	return 0;
}