#include <iostream>
#include <fstream>

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int m;
	fin >> m;
	int** adjacency_matrix = new int* [m];
	for (int i = 0; i < m; i++) {
		adjacency_matrix[i] = new int[m];
		for (int j = 0; j < m; j++) {
			fin >> adjacency_matrix[i][j];
		}
	}
	bool undirected_graph = true;
	for (int i = 1; i < m; i++) {
		for (int j = 0; j <= i; j++) {
			if (adjacency_matrix[i][j] != adjacency_matrix[j][i]) {
				undirected_graph = false;
				break;
			}
			else if (i == j && adjacency_matrix[i][j] == 1) {
				undirected_graph = false;
				break;
			}
		}
	}
	undirected_graph ? fout << "YES" : fout << "NO";
	fin.close();
	fout.close();
	return 0;
}