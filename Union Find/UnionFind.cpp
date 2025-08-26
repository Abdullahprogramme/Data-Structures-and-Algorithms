// Union-Find (Disjoint Set Union) implementation in C++

#include <vector>
#include <numeric>
using namespace std;

class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;

    public:
        UnionFind(int size) : parent(size), rank(size, 0) {
            // iota(parent.begin(), parent.end(), 0);

            // Another way to initialize the parent array
            for (int i = 0; i < size; ++i) {
                parent[i] = i;
            }
        }

        int find(int u) {
            if (parent[u] != u) {
                parent[u] = find(parent[u]);  // Path compression
            }
            return parent[u];
        }

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
