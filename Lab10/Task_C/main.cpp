#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Graph
{
private:
    int V, E;
    vector< pair<int, pair<int, int>> > edges;
    int* parent;

public:
    Graph(int V, int E)
        : V(V), E(E), parent(nullptr) {}

    void addEdge(int u, int v, int w)
    {
        edges.push_back({ w, {u, v} });
    }

    int find(int);
    long long int kruskalMST();
};

int Graph::find(int vertex)
{
    if (vertex != parent[vertex])
        parent[vertex] = find(parent[vertex]);
    return parent[vertex];
}

long long int Graph::kruskalMST()
{
    long long int mst_weight = 0;

    sort(edges.begin(), edges.end());

    parent = new int[V];

    for (int i = 0; i < V; i++)
        parent[i] = i;

    vector< pair<int, pair<int, int>> >::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = find(u);
        int set_v = find(v);

        if (set_u != set_v)
        {
            mst_weight += it->first;

            parent[set_u] = set_v;
        }
    }

    return mst_weight;
}

int main()
{
    int n, m;
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");
    fin >> n >> m;
    vector<pair<int, int>> coordinates;
    Graph g(n, m);
    int a, b, w;

    for (int i = 0; i < m; i++)
    {
        fin >> a >> b >> w;
        
        g.addEdge(a - 1, b - 1, w);
    }

    fout << g.kruskalMST();

    fin.close();
    fout.close();
    return 0;
}