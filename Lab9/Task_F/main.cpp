#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<int> whoFirstVisit;
vector<bool> whoWin;

bool DFS(int v, bool firstPlayer) {
	if (graph[v].empty())
		return !firstPlayer;

	if (whoFirstVisit[v] != 0) {
		return firstPlayer == whoFirstVisit[v] % 2 ? whoWin[v] : !whoWin[v];
	}

	bool firstWin;

	firstPlayer ? whoFirstVisit[v] = 1 : whoFirstVisit[v] = 2;

	for (int vertex : graph[v]) {
		
		if (vertex == graph[v][0])
			firstWin = DFS(vertex, !firstPlayer);
		else
			firstPlayer ? firstWin |= DFS(vertex, !firstPlayer) : firstWin &= DFS(vertex, !firstPlayer);
		
		if (firstPlayer == firstWin)
			break;
	}

	firstWin ? whoWin[v] = 1 : whoWin[v] = 2;
	
	return firstWin;
}

int main() {
	int n, m, startPosition;
	ifstream fin("game.in");
	ofstream fout("game.out");
	fin >> n >> m >> startPosition;
	graph.resize(n, vector<int>());
	whoFirstVisit.assign(n, 0);
	whoWin.resize(n);
	int a, b;
	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
	}

	DFS(startPosition - 1, true) ? fout << "First player wins" : fout << "Second player wins";

	fin.close();
	fout.close();
	return 0;
}