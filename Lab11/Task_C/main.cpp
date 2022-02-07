#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<unsigned long> dist;

void Relax(int u, int v, int w) {
    if (dist[v] > dist[u] + w)
        dist[v] = dist[u] + w;
}

void Dijkstra(int V, int start) {

    vector<bool> used;
    dist.resize(V, ULONG_MAX);
    dist[start] = 0;
    used.resize(V, false);

    for (int i = 0; i < (int)graph[start].size(); i++)
    {
        dist[graph[start][i].first] = graph[start][i].second;
    }
    set<pair<unsigned long, int> > pq;
    for (int i = 0; i < V; i++)
        pq.insert({ dist[i], i });
    while (!pq.empty())
    {
        pair<int, int> item = *pq.begin();
        pq.erase(pq.begin());
        int v = item.second;
        for (int i = 0; i < (int)graph[v].size(); i++)
        {
            if (dist[graph[v][i].first] > dist[v] + graph[v][i].second)
            {
                pq.erase(pq.find({ dist[graph[v][i].first], graph[v][i].first }));
                pq.insert({ dist[v] + graph[v][i].second, graph[v][i].first });
                dist[graph[v][i].first] = dist[v] + graph[v][i].second;
            }
        }
    }
}

int main() {
    int n, m;
    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");
    fin >> n >> m;
    int u, v, w;

    graph.resize(n);
    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> w;
        graph[u - 1].push_back({ v - 1, w });
        graph[v - 1].push_back({ u - 1, w });
    }

    Dijkstra(n, 0);
    for (int i = 0; i < n; ++i) {
        if (dist[i] != ULONG_MAX)
            fout << dist[i] << " ";
        else
            abort();
    }

    fin.close();
    fout.close();
    return 0;
}