#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

bool IsBipartite(int n, const vector<pair<int, int>>& edges, set<int>& setA, set<int>& setB) {
    // make a adjacency list
    vector<vector<int>> adj(n);
    for (const auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    vector<int> color(n, -1);
    for (int start = 0; start < n; ++start) {
        vector<int> queue;  

        if (color[start] == -1) {
            queue.push_back(start);
            color[start] = 0;

            while (!queue.empty()) {
                int node = queue.back();
                queue.pop_back();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        if (color[neighbor] == 0) {
                            setA.insert(neighbor - 1);
                        } else {
                            setB.insert(neighbor - 1);
                        }

                        queue.push_back(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return false; // Found same color on both ends of an edge
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    int n = 5; // Number of vertices
    vector<pair<int, int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0}, // This edge creates an odd-length cycle
        {3, 4}
    };

    set<int> setA, setB;

    if (IsBipartite(n, edges, setA, setB)) {
        cout << "The graph is bipartite." << endl;
        
        cout << "Set A: {";
        for (auto i = setA.begin(); i != setA.end(); ++i) {
            if (i != setA.begin()) cout << " ";
            cout << *i;
        }
        cout << "}" << endl;

        cout << "Set B: {";
        for (auto i = setB.begin(); i != setB.end(); ++i) {
            if (i != setB.begin()) cout << " ";
            cout << *i;
        }
        cout << "}" << endl;

    } else {
        cout << "The graph is not bipartite." << endl;
    }

    return 0;
}