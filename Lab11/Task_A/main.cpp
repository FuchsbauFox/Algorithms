#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits.h>

using namespace std;

int** graph;
vector<long long int> dist;

void Relax(int u, int v, int w) {
    if (dist[v] > dist[u] + w)
        dist[v] = dist[u] + w;
}

long long int Dijkstra(int V, int start, int finish) {

    vector<bool> used;
    dist.resize(V, LLONG_MAX);
    dist[start] = 0;
    used.resize(V, false);

    for (int i = 0; i < V; i++) {
        int vertex = -1;
        for (int j = 0; j < V; j++) {
            if (!used[j] && (vertex == -1 || dist[j] < dist[vertex]))
                vertex = j;
        }
        if (dist[vertex] == LLONG_MAX)
            break;
        used[vertex] = true;
        for (int j = 0; j < V; ++j) {
            if (graph[vertex][j] != 0 && graph[vertex][j] != -1)
                Relax(vertex, j, graph[vertex][j]);
        }
    }
    return dist[finish] != LLONG_MAX ? dist[finish] : -1;
}

int main()
{
    int n, s, f;
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");

    fin >> n >> s >> f;
    graph = new int* [n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            fin >> graph[i][j];
        }
    }

    fout << Dijkstra(n, s - 1, f - 1);

    fin.close();
    fout.close();
    return 0;
}