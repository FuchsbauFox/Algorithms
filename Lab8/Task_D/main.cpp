#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
bool* used;
int* comp;


void DFS(int v, int c_num) {
	used[v] = true;
	comp[v] = c_num;
	for (int i = 0; i < graph[v].size(); i++) {
		if (!used[graph[v][i]])
			DFS(graph[v][i], c_num);
	}
}

int main() {
	int n, m;
	ifstream fin("components.in");
	ofstream fout("components.out");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	used = new bool[n];
	fill(used, used + n, false);
	comp = new int[n];
	int a, b;
	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}
	int comp_num = 1;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			DFS(i, comp_num);
			comp_num++;
		}
	}
	fout << comp_num - 1 << endl;
	for (int i = 0; i < n; i++) {
		fout << comp[i] << " ";
	}
	fin.close();
	fout.close();
	delete[] used;
	delete[] comp;
	return 0;
}