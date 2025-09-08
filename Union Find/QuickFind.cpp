// Simpler version of the UnionFind.cpp

#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class QuickFind {
    private:
        int n;
        vector<int> id;

    public:
        QuickFind(int size) {
            n = size;
            id.resize(n);
            iota(id.begin(), id.end(), 0);
        }

        bool connected(int p, int q) {
            return find(p) == find(q);
        }

        // O(n) time complexity
        void unite(int p, int q) {
            int pID = find(p);
            int qID = find(q);
            if (pID != qID) {
                for (int i = 0; i < id.size(); i++) {
                    if (id[i] == pID) { // Making all elements connected to pID point to qID
                        id[i] = qID;
                    }
                }
            }
        }

        // O(1) time complexity
        int find(int p) {
            return id[p];
        }
};
