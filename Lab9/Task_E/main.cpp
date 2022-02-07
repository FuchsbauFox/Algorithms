#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<int> order;
bool* used;

void DFS(int v) {
	used[v] = true;

	for (int vertex : graph[v]) {
		if (!used[vertex])
			DFS(vertex);
	}

	order.push_back(v);
}

void topological_sort(int n) {

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			DFS(i);
		}
	}
}

bool homiltonian(int v) {
	if (v == 0)
		return true;
	for (int vertex : graph[order[v]]) {
		if (vertex == order[v - 1])
			return homiltonian(v - 1);
	}
	return false;
}

int main() {
	int n, m;
	ifstream fin("hamiltonian.in");
	ofstream fout("hamiltonian.out");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	used = new bool[n];
	int a, b;
	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
	}

	fill(used, used + n, false);
	topological_sort(n);

	homiltonian(n - 1) ? fout << "YES" : fout << "NO";

	fin.close();
	fout.close();
	delete[] used;
	return 0;
}