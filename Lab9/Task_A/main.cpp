#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
bool* used;
vector<int> order;
vector<int> color;

bool cycliq(int v) {
	if (color[v] == 2)
		return true;
	color[v] = 1;
	for (int vetrex : graph[v]) {
		if (color[vetrex] == 0) {
			if (!cycliq(vetrex)) {
				return false;
			}
		}
		else if (color[vetrex] == 1) {
			return false;
		}
	}
	color[v] = 2;
	return true;
}

void DFS(int v) {
	used[v] = true;

	for (int vertex: graph[v]) {
		if (!used[vertex])
			DFS(vertex);
	}

	order.push_back(v);
}

void topological_sort(int n) {
	fill(used, used + n, false);

	for (int i = 0; i < n; i++) {
		if (!cycliq(i)) {
			order.push_back(-2);
			return;
		}
	}

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			DFS(i);
		}
	}
}

int main() {
	int n, m;
	ifstream fin("topsort.in");
	ofstream fout("topsort.out");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	color.resize(n, 0);
	used = new bool[n];
	int a, b;

	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
	}

	topological_sort(n);

	vector<int>::iterator it = order.end();
	do {
		it--;
		fout << *it + 1 << ' ';
	} while (it != order.begin());

	fin.close();
	fout.close();
	delete[] used;
	return 0;
}