#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph, tgraph;
vector<int> order;
int* component;
bool* used;

void dfs1(int v) {
	used[v] = true;
	for (int vertex : graph[v]) {
		if (!used[vertex])
			dfs1(vertex);
	}
	order.push_back(v);
}

void dfs2(int v, int c_num) {
	used[v] = true;
	component[v] = c_num;
	for (int vertex : tgraph[v]) {
		if (!used[vertex])
			dfs2(vertex, c_num);
	}
}

int main() {
	int n, m;
	ifstream fin("cond.in");
	ofstream fout("cond.out");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	tgraph.resize(n, vector<int>());
	used = new bool[n];
	component = new int[n];
	int a, b;
	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
		tgraph[b - 1].push_back(a - 1);
	}

	fill(used, used + n, 0);
	for (int i = 0; i < n; i++) {
		if (!used[i])
			dfs1(i);
	}

	int component_number = 0;
	fill(used, used + n, 0);
	for (int i = n - 1; i >= 0; i--) {
		if (!used[order[i]]) {
			component_number++;
			dfs2(order[i], component_number);
		}
	}

	fout << component_number << '\n';
	for (int i = 0; i < n; i++) {
		fout << component[i] << ' ';
	}

	fin.close();
	fout.close();
	delete[] used;
	return 0;
}