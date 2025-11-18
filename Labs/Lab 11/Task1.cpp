#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

pair<vector<int>, bool> CycleDetection(int n, const vector<pair<int, int>>& edges) {
    UnionFind uf(n);
    vector<int> cycleEdges;
    int cycleCount = 0;

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        if (uf.find(u) == uf.find(v)) {
            cycleCount++;
        } else {
            uf.unite(u, v);
        }
    }

    set<int> vertices;
    for (auto [u, v] : edges) {
        vertices.insert(u);
        vertices.insert(v);
    }
    vector<int> verticesVec(vertices.begin(), vertices.end());

    if (cycleCount > 0) {
        for (const auto& edge : edges) {
            if (uf.find(edge.first) == uf.find(edge.second)) {
                cycleEdges.push_back(edge.first);
                cycleEdges.push_back(edge.second);
            }
        }
        for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
            const auto& edge = *it;
            if (uf.find(edge.first) == uf.find(edge.second)) {
                cycleEdges.push_back(edge.first);
                cycleEdges.push_back(edge.second);
            }
        }
    }

    return {cycleEdges, cycleCount > 0};
}

int main() {
    int n = 5; // Number of nodes
    vector<pair<int, int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 1},
        {2, 3},
        {3, 2}
    };

    auto [cycleEdges, hasCycle] = CycleDetection(n, edges);
    if (hasCycle) {
        cout << "Cycle detected with edges: ";
        for (size_t i = 0; i < cycleEdges.size(); i += 2) {
            cout << "(" <<  cycleEdges[i] << " -> " << cycleEdges[i + 1] << ") ";
        }
        cout << endl;
    } else {
        cout << "No cycle detected." << endl;
    }

    return 0;
}