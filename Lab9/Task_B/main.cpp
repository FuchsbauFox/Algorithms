#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
bool* used;
vector<int> color;
vector<int> cycle;
int cycle_vetrex = -1;

bool cycliq(int v) {
	if (color[v] == 2)
		return false;
	color[v] = 1;
	for (int vetrex : graph[v]) {
		if (color[vetrex] == 0) {
			if (cycliq(vetrex)) {
				if (cycle_vetrex != vetrex && cycle_vetrex != -1)
					cycle.push_back(v);
				else
					cycle_vetrex = -1;
				return true;
			}
		}
		else if (color[vetrex] == 1) {
			cycle_vetrex = vetrex;
			cycle.push_back(v);
			return true;
		}
	}
	color[v] = 2;
	return false;
}

bool searchCycle(int n) {
	for (int i = 0; i < n; i++) {
		if (cycliq(i)) {
			return true;
		}
	}
	return false;
}

int main() {
	int n, m;
	ifstream fin("cycle.in");
	ofstream fout("cycle.out");
	fin >> n >> m;
	graph.resize(n, vector<int>());
	color.resize(n, 0);
	used = new bool[n];
	int a, b;

	for (int i = 0; i < m; i++) {
		fin >> a >> b;
		graph[a - 1].push_back(b - 1);
	}
	
	if (searchCycle(n)) {
		fout << "YES\n";
		vector<int>::iterator it = cycle.end();
		do {
			it--;
			fout << *it + 1 << ' ';
		} while (it != cycle.begin());
	}
	else
		fout << "NO\n";
	fin.close();
	fout.close();
	delete[] used;
	return 0;
}