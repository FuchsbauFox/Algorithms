#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int** graph;
vector<long long int> dist;

void Relax(int u, int v, int w) {
    if (dist[v] > dist[u] + w)
        dist[v] = dist[u] + w;
}

void Dijkstra(int V, int start) {

    vector<bool> used;
    dist.clear();
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
}

int main() {
    int n, m;
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");
    fin >> n >> m;
    int u, v, w; 
    graph = new int* [n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            i == j ? graph[i][j] = 0 : graph[i][j] = -1;
        }
    }
    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> w;
        graph [u - 1][v - 1] = w;
    }
    for (int i = 0; i < n; ++i) {
        Dijkstra(n, i);
        for (int j = 0; j < n; ++j) {
            fout << dist[j] << ' ';
        }
        fout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}

//int main() {
//    int n, m;
//    ifstream fin("pathsg.in");
//    ofstream fout("pathsg.out");
//    fin >> n >> m;
//    int u, v, w;
//    Graph G(n);
//    for (int i = 0; i < m; ++i) {
//        fin >> u >> v >> w;
//        G.PushEdge(w, u - 1, v - 1);
//    }
//    for (int i = 0; i < n; ++i) {
//        G.BellmanFord(i);
//        G.Get(fout, i);
//    }
//    fin.close();
//    fout.close();
//    return 0;
//}