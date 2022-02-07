#include <iostream>
#include <fstream>

using namespace std;

int main() {
	int m, n;
	ifstream fin("binsearch.in");
	ofstream fout("binsearch.out");
	fin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> arr[i];
	}
	fin >> m;
	int* search = new int[m];
	for (int i = 0; i < m; i++) {
		fin >> search[i];
	}
	int l, r, middle;
	for (int i = 0; i < m; i++) {
		l = -1;
		r = n - 1;
		while (l < r - 1)
		{
			middle = (l + r) / 2;
			if (arr[middle] < search[i])
				l = middle;
			else
				r = middle;
		}
		if (arr[r] == search[i])
			fout << r + 1 << " ";
		else
			fout << -1 << " ";
		l = -1;
		r = n;
		while (l < r - 1)
		{
			middle = (l + r) / 2;
			if (arr[middle] > search[i])
				r = middle;
			else
				l = middle;
		}
		if (arr[l] == search[i])
			fout << l + 1 << endl;
		else
			fout << -1 << endl;
	}
	fin.close();
	fout.close();
	return 0;
}