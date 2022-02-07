#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<int> whoFirstVisit;
vector<bool> whoWin;

int main() {
	int n, m;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	whoFirstVisit.assign(n, 0);
	whoWin.resize(n);
	int a, b;
	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}
	for (const auto v : graph) {
		fout << v.size() << ' ';
	}
	fin.close();
	fout.close();
	return 0;
}