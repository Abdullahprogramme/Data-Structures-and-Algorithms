#pragma once

#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent, size;

public:
    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int p) {
        if (p != parent[p]) {
            parent[p] = find(parent[p]); // path compression
        }
        
        return parent[p];
    }

    void unify(int p, int q) {
        int root1 = find(p);
        int root2 = find(q);
        if (root1 == root2) return;

        if (size[root1] > size[root2]) // union by size
            std::swap(root1, root2);
        
        parent[root1] = root2;
        size[root2] += size[root1];
    }
};

