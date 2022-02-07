#include <iostream>
#include <vector>
#include <fstream>

using namespace std;



int main() {
	ifstream fin("knight2.in");
	ofstream fout("knight2.out");
	int n, m;
	fin >> n >> m;
	int** field;
	field = new int* [n];

	for (int i = 0; i < n; ++i) {
		field[i] = new int[m];
		for (int j = 0; j < m; ++j) {
			field[i][j] = 0;
		}
	}
	field[0][0] = 1;

	int i = 0, j = 1;
	while (i != n - 1 || j != m - 1) {
		int x = i, y = j;
		while (y >= 0 || x < n - 1) {
			if (x - 2 >= 0) {
				if (y - 1 >= 0) {
					field[x][y] += field[x - 2][y - 1];
				}
				if (y + 1 < m) {
					field[x][y] += field[x - 2][y + 1];
				}
			}
			if (y - 2 >= 0) {
				if (x - 1 >= 0) {
					field[x][y] += field[x - 1][y - 2];
				}
				if (x + 1 < n) {
					field[x][y] += field[x + 1][y - 2];
				}
			}
			y--;
			x++;
		}
		for (int ii = 0; ii < n; ++ii) {
			for (int jj = 0; jj < m; ++jj) {
				fout << field[ii][jj] << ' ';
			}
			fout << endl;
		}
		fout << "============\n";
		j == m - 1 ? i++ : j++;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << field[i][j] << ' ';
		}
		cout << endl;
	}

	field[n - 1][m - 1] += field[n - 3][m - 2] + field[n - 3][m - 2];

	fout << field[n - 1][m - 1];
	fin.close();
	fout.close();
	return 0;
}