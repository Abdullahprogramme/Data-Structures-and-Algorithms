// Quick Union
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class QuickUnion {
    private:
        int n;
        vector<int> id;

    public:
        QuickUnion(int size) {
            n = size;
            id.resize(n);
            iota(id.begin(), id.end(), 0);
        }

        bool connected(int p, int q) {
            return find(p) == find(q);
        }

        // O(h) time complexity, where h is the height of the tree
        void unite(int p, int q) {
            int pID = find(p);
            int qID = find(q);
            if (pID != qID) { // Making the root of p point to the root of q
                id[pID] = qID;
            }
        }

        // O(h) time complexity, where h is the height of the tree
        int find(int p) {
            while (p != id[p]) {
                p = id[p];
            }
            return p;
        }
};

// Worst case:
// The worst case occurs when the tree is completely unbalanced, resembling a linked list.
// In this scenario, the time complexity for find and union operations can degrade to O(n).

// Best case:
// The best case occurs when the tree is completely balanced, with all nodes having similar depths.
// In this scenario, the time complexity for find and union operations is nearly constant, O(log n), due to the tree's balanced nature.


/* Question:
{0}, {1},    {9},       {6},    {7},      {8}
           {2} {4}      {5}
               {3}

Which is not the valid way to implement unify(3, 5)?
A. Set parent[6] = 9
B. Set parent[9] = 6
C. Set parent[3] = 5
D. Set parent[2] = parent[3] = parent[4] = parent[9] = 6

Answer: C, since it directly connects 3 to 5 by removing it from its original component. 
If convention is reversed then still it is placing 5 under 3, which is not valid.
*/
