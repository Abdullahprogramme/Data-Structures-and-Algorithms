#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <tuple>


using namespace std;

class DisjointSet {
    private:
        unordered_map<string, string> parent;

    public:

        // Time Complexity: O(n), in terms of edges: O(E)
        void makeSet(const vector<string> &elements) {
            for (const auto &e : elements) {
                parent[e] = e;
            }
        }

        // Time Complexity: O(log n) on average, in terms of edges: O(E)
        string find(const string &element) {
            if (parent[element] != element) {
                parent[element] = find(parent[element]);
            }

            return parent[element];
        }

        // Time Complexity: O(log n) on average, in terms of edges: O(E)
        void Union(const string &a, const string &b) {
            string rootA = find(a);
            string rootB = find(b);
            
            if (rootA != rootB) {
                parent[rootB] = rootA;
            }
        }
};

// edge list format
using Graph = vector<tuple<string, string, int>>;

pair<Graph, int> Kruskal_MST(const Graph &edges, const vector<string> &vertices) {
    Graph mst;
    DisjointSet ds;
    ds.makeSet(vertices);
    int total_weight = 0;

    // sort edges by weight
    auto sorted_edges = edges;

    // Sorting takes O(E log E)
    sort(sorted_edges.begin(), sorted_edges.end(), [](const auto &a, const auto &b) {
        return get<2>(a) < get<2>(b);
    });

    for (const auto &edge : sorted_edges) {
        const string &u = get<0>(edge);
        const string &v = get<1>(edge);
        int w = get<2>(edge);

        if (ds.find(u) != ds.find(v)) {
            ds.Union(u, v);
            mst.push_back({u, v, w});
            total_weight += w;
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

    auto [mst, total_weight] = Kruskal_MST(edges, vertices);

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mst) {
        cout << get<0>(edge) << " -- " << get<1>(edge) << " == " << get<2>(edge) << "\n";
    }
    cout << "Total weight: " << total_weight << "\n";

    return 0;
}