// Minimum Spanning Tree Algorithms: Kruskal's and Prim's

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DisjointSet {
public:
    vector<int> parent, rank;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);
        if (xroot == yroot) return;
        if (rank[xroot] < rank[yroot]) parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot]) parent[yroot] = xroot;
        else { parent[yroot] = xroot; rank[xroot]++; }
    }
};

int kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DisjointSet ds(n);
    int mstWeight = 0;
    for (Edge& e : edges) {
        if (ds.find(e.u) != ds.find(e.v)) {
            ds.unite(e.u, e.v);
            mstWeight += e.weight;
        }
    }
    return mstWeight;
}

int primMST(int n, vector<vector<pair<int, int>>>& adj) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<bool> visited(n, false);
    pq.push({0, 0});
    int mstWeight = 0;
    while (!pq.empty()) {
        auto [weight, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        mstWeight += weight;
        for (auto& [v, w] : adj[u]) {
            if (!visited[v]) pq.push({w, v});
        }
    }
    return mstWeight;
}

vector<Edge> generateEdges(int n, int density) {
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 100 < density) {
                int w = rand() % 100 + 1;
                edges.push_back({i, j, w});
            }
        }
    }
    return edges;
}

vector<vector<pair<int, int>>> buildAdjList(int n, const vector<Edge>& edges) {
    vector<vector<pair<int, int>>> adj(n);
    for (const Edge& e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }
    return adj;
}

int main() {
    srand(time(0));
    vector<int> sizes = {10, 50, 100, 200, 500};
    vector<int> densities = {20, 40, 60, 80, 100};
    cout << "Nodes\tEdges\tDensity\tKruskal(ms)\tPrim(ms)" << endl;
    for (int i = 0; i < sizes.size(); i++) {
        int n = sizes[i];
        int density = densities[i];
        vector<Edge> edges = generateEdges(n, density);
        vector<vector<pair<int, int>>> adj = buildAdjList(n, edges);

        clock_t start = clock();
        int w1 = kruskalMST(n, edges);
        clock_t end = clock();
        double kruskalTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;

        start = clock();
        int w2 = primMST(n, adj);
        end = clock();
        double primTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;

        cout << n << "\t" << edges.size() << "\t" << density << "%\t"
             << kruskalTime << "\t\t" << primTime << endl;
    }
    return 0;
}
