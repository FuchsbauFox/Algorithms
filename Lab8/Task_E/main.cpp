#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
bool* used;
int* way;


void BFS(int v) {
	used[v] = true;
	way[v] = 0;
	vector<int> queue;
	queue.push_back(v);
	while (!queue.empty()) {
		v = queue[0];
		queue.erase(queue.begin());
		for (int i = 0; i < graph[v].size(); i++) {
			if (!used[graph[v][i]]) {
				used[graph[v][i]] = true;
				way[graph[v][i]] = way[v] + 1;
				queue.push_back(graph[v][i]);
			}
		}
	}
}

int main() {
	int n, m;
	ifstream fin("pathbge1.in");
	ofstream fout("pathbge1.out");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	used = new bool[n];
	fill(used, used + n, false);
	way = new int[n];
	int a, b;
	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}
	BFS(0);
	for (int i = 0; i < n; i++) {
		fout << way[i] << " ";
	}
	fin.close();
	fout.close();
	delete[] used;
	delete[] way;
	return 0;
}