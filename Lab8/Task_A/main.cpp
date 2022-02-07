#include <iostream>
#include <fstream>

using namespace std;

int main() {
	int m, n;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> m >> n;
	int** adjacency_matrix = new int* [m];
	for (int i = 0; i < m; i++) {
		adjacency_matrix[i] = new int[m];
		for (int j = 0; j < m; j++) {
			adjacency_matrix[i][j] = 0;
		}
	}
	int a, b;
	for (int i = 0; i < n; i++) {
		fin >> a >> b;
		adjacency_matrix[a - 1][b - 1] += 1;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			fout << adjacency_matrix[i][j] << ' ';
		}
		fout << '\n';
	}
	fin.close();
	fout.close();
	return 0;
}