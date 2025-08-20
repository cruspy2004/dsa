#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& e) const {
        return weight < e.weight;
    }
};

class DisjointSet {
private:
    vector<int> parent, rank;
public:
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
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            if (rank[rx] < rank[ry]) parent[rx] = ry;
            else if (rank[rx] > rank[ry]) parent[ry] = rx;
            else {
                parent[ry] = rx;
                rank[rx]++;
            }
        }
    }
};

// Kruskal's Algorithm
vector<Edge> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DisjointSet ds(n);
    vector<Edge> mst;

    for (Edge& e : edges) {
        if (ds.find(e.u) != ds.find(e.v)) {
            mst.push_back(e);
            ds.unite(e.u, e.v);
        }
    }
    return mst;
}

// Prim's Algorithm
vector<Edge> prim(int n, vector<vector<pair<int, int>>>& adj) {
    vector<bool> visited(n, false);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    vector<Edge> mst;

    pq.push({0, {0, -1}}); // weight, {to, from}

    while (!pq.empty()) {
        auto [w, p] = pq.top(); pq.pop();
        int u = p.first, parent = p.second;

        if (visited[u]) continue;
        visited[u] = true;
        if (parent != -1) mst.push_back({parent, u, w});

        for (auto& [v, weight] : adj[u]) {
            if (!visited[v]) {
                pq.push({weight, {v, u}});
            }
        }
    }
    return mst;
}

// Complexity Analysis (for reference)
/*
Kruskal:
- Time: O(E log E) due to sorting + union-find ops (almost constant)
- Space: O(V + E)

Prim:
- Time: O((V + E) log V) using priority queue
- Space: O(V + E)
*/

int main() {
    int n = 5; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 1}, {0, 3, 4},
        {1, 2, 3}, {2, 3, 2}, {1, 4, 0},
        {3, 4, 7}
    };

    vector<Edge> mstK = kruskal(n, edges);
    cout << "Kruskal's MST:\n";
    for (Edge& e : mstK) cout << e.u << " - " << e.v << " : " << e.weight << endl;

    vector<vector<pair<int, int>>> adj(n);
    for (Edge& e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    vector<Edge> mstP = prim(n, adj);
    cout << "\nPrim's MST:\n";
    for (Edge& e : mstP) cout << e.u << " - " << e.v << " : " << e.weight << endl;

    return 0;
}
