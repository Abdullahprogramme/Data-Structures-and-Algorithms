// maze_generation.cpp
// Generate a perfect 10x10 maze using weighted quick-union (union-find).
// Output is an ASCII maze (2*rows+1 by 2*cols+1) with:
// '#' wall, ' ' path, 'S' start (top-left), 'E' end (bottom-right).

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;

struct UnionFind {
    int n;
    vector<int> parent;
    vector<int> sz;

    UnionFind(int n = 0): n(n), parent(n), sz(n,1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (x != parent[x]) {
            parent[x] = find(parent[x]); // path compression
            x = parent[x];
        }

        return x;
    }

    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;

        // weighted: attach smaller tree under larger
        if (sz[ra] < sz[rb]) swap(ra, rb);
        parent[rb] = ra;
        sz[ra] += sz[rb];

        return true;
    }
};

int main() {
    const int rows = 10;
    const int cols = 10;
    const int cells = rows * cols;

    UnionFind uf(cells);

    // list all adjacent pairs (edges between neighboring cells)
    vector<pair<int,int>> edges;
    edges.reserve(cells * 2);

    auto idx = [&](int r, int c){ 
        return r * cols + c; 
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (c + 1 < cols) edges.emplace_back(idx(r, c), idx(r, c + 1)); // right
            if (r + 1 < rows) edges.emplace_back(idx(r, c), idx(r + 1, c)); // down
        }
    }

    // shuffle edges randomly
    random_device rd;
    mt19937 gen(rd());
    shuffle(edges.begin(), edges.end(), gen);

    // ASCII grid: (2*rows+1) x (2*cols+1), walls '#', passages ' '
    int R = 2 * rows + 1;
    int C = 2 * cols + 1;
    vector<string> grid(R, string(C, '#'));

    // mark cell centers as passages
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[2 * r + 1][2 * c + 1] = ' ';
        }
    }

    // process edges; remove wall between cells when we union them
    for (auto &e : edges) {
        int a = e.first;
        int b = e.second;

        if (uf.unite(a, b)) {
            int ar = a / cols, ac = a % cols;
            int br = b / cols, bc = b % cols;

            int wr = ar + br + 1; // sum then +1 divided by 2 later as grid indices are doubled+1
            int wc = ac + bc + 1;

            // convert to grid coordinates: (ar*2+1 + br*2+1)/2 = (ar+br)+1
            grid[wr][wc] = ' ';
        }
    }

    // mark start and end
    grid[1][1] = 'S';
    grid[R - 2][C - 2] = 'E';

    // print maze
    for (int r = 0; r < R; ++r) {
        cout << grid[r] << '\n';
    }

    return 0;
}