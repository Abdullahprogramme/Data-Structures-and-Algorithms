#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

#include <vector>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <unordered_map>

using namespace std;

class Percolation {
    private:
        int n; // grid size
        vector<vector<bool>> grid; // open/blocked status of each site
        int openSites = 0; // number of open sites

        // union-find data structures
        vector<int> parent, rank;
        int Top, Bottom;

        // function to convert (row, col) to 1D index
        int index(int row, int col) const {
            return row * n + col;
        }

        // find the root of the component containing x
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        // unite the components containing x and y
        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if (rootX == rootY) return;

            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }

    public:
        // creates n-by-n grid, with all sites initially blocked
        Percolation(int n_) : n(n_) {
            if (n <= 0) {
                throw invalid_argument("Grid size must be positive");
            }

            grid = vector<vector<bool>>(n, vector<bool>(n, false));
            parent.resize(n * n + 2);
            rank.resize(n * n + 2, 0);

            for (int i = 0; i < n * n + 2; ++i) {
                parent[i] = i; // each site is its own parent
            }

            // Another way
            // iota(parent.begin(), parent.end(), 0);

            Top = n * n;
            Bottom = n * n + 1;
        }

        // opens the site (row, col) if it is not open already
        void open(int row, int col) {
            if (row < 0 || row >= n || col < 0 || col >= n) {
                throw invalid_argument("Invalid site");
            }

            if (!isOpen(row, col)) {
                grid[row][col] = true;
                openSites++;

                int curr = index(row, col);

                // Connect to  top if in top row
                if (row == 0) unite(curr, Top);
                // Connect to  bottom if in bottom row
                if (row == n - 1) unite(curr, Bottom);

                // Connect to adjacent open sites
                const unordered_map<int, int> dirMap = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (const auto& [dr, dc] : dirMap) {
                    int nr = row + dr, nc = col + dc;
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && isOpen(nr, nc)) {
                        unite(curr, index(nr, nc));
                    }
                }
            }
        }

        // is the site (row, col) open?
        bool isOpen(int row, int col) {
            if (row < 0 || row >= n || col < 0 || col >= n) {
                throw invalid_argument("Invalid site");
            }

            return grid[row][col];
        }

        // is the site (row, col) full?
        bool isFull(int row, int col) {
            if (row < 0 || row >= n || col < 0 || col >= n) {
                throw invalid_argument("Invalid site");
            }

            if (!isOpen(row, col)) return false;
            return find(index(row, col)) == find(Top);
        }

        // returns the number of open sites
        int numberOfOpenSites() {
            return openSites;
        }

        // does the system percolate?
        bool percolates() {
            return find(Top) == find(Bottom);
        }

        // unit testing (required)
        static void test() {
            Percolation p(5);
            p.open(0, 0);
            p.open(1, 0);
            p.open(2, 0);
            p.open(3, 0);
            p.open(4, 0);

            // Grid will be:
            // [1, 0, 0, 0, 0]
            // [1, 0, 0, 0, 0]
            // [1, 0, 0, 0, 0]
            // [1, 0, 0, 0, 0]
            // [1, 0, 0, 0, 0]

            assert(p.percolates() == true);
            assert(p.numberOfOpenSites() == 5);
            assert(p.isFull(4, 0) == true);
            assert(p.isOpen(2, 0) == true);
            assert(p.isOpen(2, 1) == false);

            // Test invalid arguments
            try {
                p.open(-1, 0);
                assert(false);
            } catch (const invalid_argument&) {}

            try {
                p.isOpen(0, 5);
                assert(false);
            } catch (const invalid_argument&) {}

            try {
                p.isFull(5, 0);
                assert(false);
            } catch (const invalid_argument&) {}

            cout << "All Percolation tests passed!\n";
        }
};

#endif // PERCOLATION_HPP
