#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
int* color;

bool DFS_bipartite(int v, int c) {
	if (color[v] != 0)
		return true;
	color[v] = c;

	for (int vertex : graph[v]) {
		if (color[vertex] == 0) {
			if (!DFS_bipartite(vertex, c == 1 ? 2 : 1)) {
				return false;
			}
		}
		else if (color[vertex] == c) {
			return false;
		}
	}
	return true;
}

int main() {
	int n, m;
	ifstream fin("bipartite.in");
	ofstream fout("bipartite.out");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	color = new int[n];
	fill(color, color + n, 0);
	int a, b;

	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}

	for (int i = 0; i < n; i++) {
		if (!DFS_bipartite(i, 1)) {
			fout << "NO\n";
			return 0;
		}
	}
	fout << "YES\n";

	fin.close();
	fout.close();
	delete[] color;
	return 0;
}