#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <string>
#include <functional>

using namespace std;

// edge list format
using Graph = vector<tuple<string, string, int>>;

pair<Graph, int> Prims_MST(const Graph &edges, const vector<string> &vertices) {
    // build adjacency list
    unordered_map<string, vector<pair<string,int>>> adj;
    for (const auto &e : edges) {
        const string &u = get<0>(e);
        const string &v = get<1>(e);
        int w = get<2>(e);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    Graph mst;
    int total_weight = 0;
    unordered_set<string> visited;

    // min-heap of (weight, from, to)
    using Item = tuple<int, string, string>;
    priority_queue<Item, vector<Item>, greater<Item>> pq;

    // Handle disconnected graphs by running Prim from every unvisited vertex
    for (const auto &start : vertices) {
        if (visited.count(start)) continue;

        // push a dummy edge from start to start with weight 0
        pq.push({0, start, start});

        while (!pq.empty()) {
            auto [w, from, to] = pq.top();
            pq.pop();

            if (visited.count(to)) continue;

            visited.insert(to);
            if (from != to) { // skip the dummy self-edge
                mst.push_back({from, to, w});
                total_weight += w;
            }

            // push all edges from 'to' to neighbors
            for (const auto &nbr : adj[to]) {
                const string &v = nbr.first;
                int vw = nbr.second;
                if (!visited.count(v)) {
                    pq.push({vw, to, v});
                }
            }
        }
    }

    return {mst, total_weight};
}

int main() {
    // Example usage
    vector<string> vertices = {"A", "B", "C", "D"};
    Graph edges = {
        {"A", "B", 1},
        {"B", "C", 2},
        {"A", "C", 2},
        {"C", "D", 1},
        {"B", "D", 3}
    };

    auto [mst, total_weight] = Prims_MST(edges, vertices);

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mst) {
        cout << get<0>(edge) << " -- " << get<1>(edge) << " == " << get<2>(edge) << "\n";
    }
    cout << "Total weight: " << total_weight << "\n";

    return 0;
}