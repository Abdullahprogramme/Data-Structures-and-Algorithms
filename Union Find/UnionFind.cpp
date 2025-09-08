// Union-Find (Disjoint Set Union) implementation in C++

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;

    public:
        UnionFind(int size) : parent(size), rank(size, 0) {
            // parent.resize(size);
            // rank.resize(size, 0);
            // iota(parent.begin(), parent.end(), 0);

            // Another way to initialize the parent array
            for (int i = 0; i < size; ++i) {
                parent[i] = i;
            }
        }

        // O(h) time complexity, where h is the height of the tree
        int find(int u) {
            if (parent[u] != u) {
                parent[u] = find(parent[u]);  // Path compression
            }
            return parent[u];
        }

        // O(h) time complexity, where h is the height of the tree
        void unify(int u, int v) {
            int rootU = find(u);
            int rootV = find(v);
            if (rootU != rootV) {
                // Union by rank
                if (rank[rootU] > rank[rootV]) {
                    parent[rootV] = rootU;
                } else if (rank[rootU] < rank[rootV]) {
                    parent[rootU] = rootV;
                } else {
                    parent[rootV] = rootU;
                    rank[rootU]++;
                }
            }
        }
};

/*
Worst case:
The worst case occurs when the tree is completely unbalanced, resembling a linked list.
In this scenario, the time complexity for find and union operations can degrade to O(n).
*/

/*
Best case:
The best case occurs when the tree is completely balanced, with all nodes having similar depths.
In this scenario, the time complexity for find and union operations is nearly constant, O(log n), due to the tree's balanced nature.
*/

// Find number of connected components in a graph
int countComponents(int n, vector<vector<int>>& edges) {
    UnionFind uf(n);
    for (auto& edge : edges) {
        uf.unify(edge[0], edge[1]);
    }
    
    int components = 0;
    for (int i = 0; i < n; i++) {
        if (uf.find(i) == i) components++;
    }
    return components;
}

// Detect if adding an edge creates a cycle
bool hasCycle(int n, vector<vector<int>>& edges) {
    UnionFind uf(n);
    for (auto& edge : edges) {
        if (uf.find(edge[0]) == uf.find(edge[1])) {
            return true; // Cycle detected
        }
        uf.unify(edge[0], edge[1]);
    }
    return false;
}

// Kruskal's algorithm for MST
int kruskalMST(int n, vector<vector<int>>& edges) {
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        return a[2] < b[2]; // Sort by weight
    });
    
    UnionFind uf(n);
    int mstWeight = 0;
    
    for (auto& edge : edges) {
        if (uf.find(edge[0]) != uf.find(edge[1])) {
            uf.unify(edge[0], edge[1]);
            mstWeight += edge[2];
        }
    }
    return mstWeight;
}

int main() {
    // Using '/' for parent element
    UnionFind uf(5); // 5 elements: {/0, /1, /2, /3, /4}

    uf.unify(0, 1); // {/0, 1}, {2}, {3}, {4}
    uf.unify(2, 3); // {/0, 1}, {/2, 3}, {4}
    uf.unify(1, 4); // {/0, 1, 4}, {/2, 3}

    cout << uf.find(0) << endl; // Same as uf.find(1), uf.find(4)
    cout << uf.find(3) << endl; // Same as uf.find(2)

    return 0;
}