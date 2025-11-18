#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


vector<vector<int>> CycleDetection(int n, const vector<pair<int, int>>& edges) {
    // Create adjacency list
    vector<vector<int>> adj(n);
    for (const auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
    }

    // three states: 0 = unvisited, 1 = visiting, 2 = visited
    vector<int> state(n, 0);
    vector<vector<int>> cycles;

    function<bool(int, vector<int>&)> dfs = [&](int node, vector<int>& path) {
        if (state[node] == 1) {
            // Cycle detected
            auto it = find(path.begin(), path.end(), node);
            if (it != path.end()) {
                vector<int> cycle(it, path.end());
                cycle.push_back(node);
                cycles.push_back(cycle);
            }

            return true;
        }

        if (state[node] == 2) return false;

        state[node] = 1; // Mark as visiting
        path.push_back(node);

        for (int neighbor : adj[node]) {
            if (dfs(neighbor, path)) {
                // Cycle found in recursion
            }
        }

        state[node] = 2; // Mark as visited
        path.pop_back();

        return false;
    };

    for (int i = 0; i < n; ++i) {
        if (state[i] == 0) {
            vector<int> path;
            dfs(i, path);
        }
    }

    return cycles;
}

int main() {
    int n = 5;
    vector<pair<int, int>> edges = {
        {0, 1},
        {1, 2},
        {2, 0},
        {1, 3},
        {3, 4},
        {4, 1},
        {2, 3},
        {3, 2}
    };

    vector<vector<int>> cycles = CycleDetection(n, edges);

    for (const auto& cycle : cycles) {
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}