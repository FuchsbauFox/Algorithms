#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
bool* used;
int** way;
int n, m;
bool escape = false;

bool Used(int x, int y) {
	return used[graph[x][y]] ? false : true;
}

void BFS(int v, int finish) {
	used[v] = true;
	way[v][0] = 0;
	vector<int> queue;
	queue.push_back(v);
	while (!queue.empty()) {
		v = queue[0];
		if (v == finish) {
			escape = true;
			return;
		}
		queue.erase(queue.begin());
		if (v % m - 1 > -1 && graph[v / m][v % m - 1] != -1 && Used(v / m, v % m - 1)) {
			queue.push_back(graph[v / m][v % m - 1]);
			used[graph[v / m][v % m - 1]] = true;
			way[graph[v / m][v % m - 1]][0] = way[v][0] + 1;
			way[graph[v / m][v % m - 1]][1] = graph[v / m][v % m];
		}
		if (v % m + 1 < m && graph[v / m][v % m + 1] != -1 && Used(v / m, v % m + 1)) {
			queue.push_back(graph[v / m][v % m + 1]);
			used[graph[v / m][v % m + 1]] = true;
			way[graph[v / m][v % m + 1]][0] = way[v][0] + 1;
			way[graph[v / m][v % m + 1]][1] = graph[v / m][v % m];
		}
		if (v - m > -1 && graph[v / m - 1][v % m] != -1 && Used(v / m - 1, v % m)) {
			queue.push_back(graph[v / m - 1][v % m]);
			used[graph[v / m - 1][v % m]] = true;
			way[graph[v / m - 1][v % m]][0] = way[v][0] + 1;
			way[graph[v / m - 1][v % m]][1] = graph[v / m][v % m];
		}
		if (v + m < m * n && graph[v / m + 1][v % m] != -1 && Used(v / m + 1, v % m)) {
			queue.push_back(graph[v / m + 1][v % m]);
			used[graph[v / m + 1][v % m]] = true;
			way[graph[v / m + 1][v % m]][0] = way[v][0] + 1;
			way[graph[v / m + 1][v % m]][1] = graph[v / m][v % m];
		}
	}
}

int main() {
	int start, finish;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> n >> m;
	graph.resize(n, vector<int>(m));
	used = new bool[n * m];
	fill(used, used + n * m, false);
	way = new int* [n * m];
	for (int i = 0; i < n * m; i++) {
		way[i] = new int[2];
	}
	char in;
	for (int i = 0; i < m * n; i++) {
		fin >> in;
		if (in != '#')
			graph[i / m][i % m] = i;
		else
			graph[i / m][i % m] = -1;
		if (in == 'S')
			start = i;
		if (in == 'T')
			finish = i;
	}
	BFS(finish, start);
	int vertex = start;
	if (escape) {
		fout << way[vertex][0] << '\n';
		while (vertex != finish) {
			if (vertex % m - 1 > -1 && way[vertex][1] == graph[vertex / m][vertex % m - 1])
				fout << "L";
			if (vertex % m + 1 < m && way[vertex][1] == graph[vertex / m][vertex % m + 1])
				fout << "R";
			if (vertex - m > -1 && way[vertex][1] == graph[vertex / m - 1][vertex % m])
				fout << "U";
			if (vertex + m < m * n && way[vertex][1] == graph[vertex / m + 1][vertex % m])
				fout << "D";
			vertex = way[vertex][1];
		}
	}
	else
		fout << "-1";
	fin.close();
	fout.close();
	delete[] used;
	return 0;
}