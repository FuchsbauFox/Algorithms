#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class Graph
{
private:
    int V;
    vector< pair<int, pair<int, int>> > edges;
    int* parent;

public:
    Graph(int V)
        : V(V), parent(nullptr) {}

    void addEdge(int u, int v, int w)
    {
        edges.push_back({ w, {u, v} });
    }

    int find(int);
    double kruskalMST();
};

int Graph::find(int vertex)
{
    if (vertex != parent[vertex])
        parent[vertex] = find(parent[vertex]);
    return parent[vertex];
}

double Graph::kruskalMST()
{
    double mst_weight = 0;

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
            mst_weight += sqrt(it->first);

            parent[set_u] = set_v;
        }
    }

    return mst_weight;
}

int costEdge(pair<int, int> coor_1, pair<int, int> coor_2)
{
    return pow(coor_1.first - coor_2.first, 2) + pow(coor_1.second - coor_2.second, 2);

}

int main()
{
    int n;
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");
    fin >> n;
    vector<pair<int, int>> coordinates;
    Graph g(n);
    int a, b;

    for (int i = 0; i < n; i++)
    {
        fin >> a >> b;
        coordinates.push_back({ a, b });
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            g.addEdge(i, j, costEdge(coordinates[i], coordinates[j]));
        }
    }

    fout << setprecision(15) << g.kruskalMST();

    fin.close();
    fout.close();
    return 0;
}