#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

class ShortestPath {
    private:
        unordered_map<string, vector<pair<string, int>>> adj;

        static const int INF = numeric_limits<int>::max() / 4;

        vector<string> reconstruct_path(const unordered_map<string, string> &prev, const string &src, const string &dest) {
            vector<string> path;

            if (prev.find(dest) == prev.end() && src != dest) return path;

            string cur = dest;
            while (true) {
                path.push_back(cur);
                if (cur == src) break;

                auto it = prev.find(cur);
                if (it == prev.end()) { 
                    path.clear(); 
                    break; 
                }

                cur = it->second;
            }

            reverse(path.begin(), path.end());
            return path;
        }

    public:
        ShortestPath() {}

        void addEdge(const string &u, const string &v, int w) {
            adj[u].push_back({v, w});
            // ensure node exists in map even if no outgoing edges
            if (adj.find(v) == adj.end()) adj[v] = {};
        }

        void printGraph() const {
            for (const auto &pair : adj) {
                const string &node = pair.first;
                const auto &neighbors = pair.second;

                cout << node << " -> ";
                for (const auto &nbr : neighbors) cout << "(" << nbr.first << ", " << nbr.second << ") ";
                cout << '\n';
            }
        }

        // Dijkstra's algorithm (non-negative weights required)
        void dijkstra(const string &start) {
            cout << "Dijkstra's algorithm from node: " << start << "\n";

            // prepare distances and predecessor
            unordered_map<string, int> dist;
            unordered_map<string, string> prev;
            for (const auto &p : adj) dist[p.first] = INF;

            if (dist.find(start) == dist.end()) {
                cout << "Start node '" << start << "' not present in graph.\n";
                return;
            }

            dist[start] = 0;

            using PQItem = pair<int, string>; // (distance, node)
            priority_queue<PQItem, vector<PQItem>, greater<PQItem>> pq;
            pq.push({0, start});

            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d != dist[u]) continue; // stale entry

                for (const auto &edge : adj.at(u)) {
                    const string &v = edge.first; // neighbor
                    int w = edge.second; // weight

                    if (w < 0) {
                        // Dijkstra does not support negative weights
                        cout << "Warning: negative edge weight detected (" << u << "->" << v << ", " << w << ").\n";
                    }

                    // Edge relaxation
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }

            // print results
            cout << "Shortest distances from " << start << ":\n";
            for (const auto &p : dist) {
                cout << "  " << p.first << ": ";

                if (p.second >= INF/2) cout << "unreachable\n";
                else cout << p.second << '\n';
            }

            cout << "Paths:\n";
            for (const auto &p : dist) {
                if (p.second >= INF/2) continue;
                auto path = reconstruct_path(prev, start, p.first);

                cout << "  " << p.first << ": ";
                for (size_t i = 0; i < path.size(); ++i) {
                    if (i) cout << " -> ";
                    cout << path[i];
                }
                cout << '\n';
            }
        }

        // Bellman-Ford algorithm (handles negative weights, detects negative cycles)
        void bellmanFord(const string &start) {
            cout << "Bellman-Ford algorithm from node: " << start << "\n";

            // build vertex list and edge list
            vector<string> vertices;
            unordered_map<string, int> idx;

            for (const auto &p : adj) {
                vertices.push_back(p.first);
            }
            sort(vertices.begin(), vertices.end()); // sorting the vertices
            for (size_t i = 0; i < vertices.size(); ++i) idx[vertices[i]] = (int)i;

            vector<tuple<string, string, int>> edges; // edge list (u, v, weight)
            for (const auto &p : adj) {
                const string &u = p.first;
                for (const auto &e : p.second) edges.emplace_back(u, e.first, e.second);
            }

            unordered_map<string, long long> dist;
            unordered_map<string, string> prev;

            for (const auto &v : vertices) dist[v] = LLONG_MAX/4; // initializing with large value
            if (dist.find(start) == dist.end()) {
                cout << "Start node '" << start << "' not present in graph.\n";
                return;
            }
            dist[start] = 0;

            size_t V = vertices.size();

            // relax edges V - 1 times
            for (size_t i = 0; i + 1 < V; ++i) {
                bool any = false;

                for (const auto &ed : edges) {
                    const string &u = get<0>(ed); // origin
                    const string &v = get<1>(ed); // destination
                    int w = get<2>(ed); // weight

                    // Edge relaxation
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        prev[v] = u;
                        any = true;
                    }
                }

                if (!any) break;
            }

            // check for negative-weight cycles
            bool negative_cycle = false;

            for (const auto &ed : edges) {
                const string &u = get<0>(ed); // origin
                const string &v = get<1>(ed); // destination
                int w = get<2>(ed); // weight

                if (dist[u] + w < dist[v]) { 
                    negative_cycle = true; 
                    break; 
                }
            }

            if (negative_cycle) {
                cout << "Graph contains a negative-weight cycle reachable from the source.\n";
                // It's useful to try to report nodes in cycle, but that's more code. We stop here.
                return;
            }

            // print results
            cout << "Shortest distances from " << start << ":\n";
            for (const auto &p : dist) {
                cout << "  " << p.first << ": ";

                if (p.second > LLONG_MAX/8) cout << "unreachable\n";
                else cout << p.second << '\n';
            }

            cout << "Paths:\n";
            for (const auto &p : dist) {
                if (p.second > LLONG_MAX/8) continue;

                // reconstruct path using 'prev'
                vector<string> path;
                string cur = p.first;

                if (cur == start) { 
                    cout << "  " << cur << "\n"; 
                    continue; 
                }

                while (true) {
                    path.push_back(cur);
                    if (cur == start) break;

                    auto it = prev.find(cur);
                    if (it == prev.end()) { 
                        path.clear(); 
                        break; 
                    }
                    cur = it->second;
                }

                reverse(path.begin(), path.end());
                if (path.empty()) continue;

                cout << "  " << p.first << ": ";
                for (size_t i = 0; i < path.size(); ++i) {
                    if (i) cout << " -> ";
                    cout << path[i];
                }
                cout << '\n';
            }
        }
};

// Demo main: shows Dijkstra on a non-negative graph, Bellman-Ford on graph with negative edges and negative-cycle detection
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example 1: non-negative graph (Dijkstra)
    ShortestPath sp1;
    sp1.addEdge("S", "A", 4);
    sp1.addEdge("S", "E", 5);
    sp1.addEdge("A", "B", 2);
    sp1.addEdge("B", "C", 3);
    sp1.addEdge("C", "D", 2);
    sp1.addEdge("E", "D", -3); // negative edge - Dijkstra will warn but Bellman-Ford will handle
    cout << "--- Graph (for Dijkstra demo) ---\n";
    sp1.printGraph();
    cout << "\n";
    sp1.dijkstra("S");
    cout << "\n";

    // Example 2: negative edges but no negative cycle (Bellman-Ford)
    ShortestPath sp2;
    sp2.addEdge("S", "A", 4);
    sp2.addEdge("S", "B", 5);
    sp2.addEdge("A", "C", -3);
    sp2.addEdge("B", "C", 2);
    sp2.addEdge("C", "D", 2);
    cout << "--- Graph (for Bellman-Ford demo) ---\n";
    sp2.printGraph();
    cout << "\n";
    sp2.bellmanFord("S");
    cout << "\n";

    // Example 3: negative cycle detection
    ShortestPath sp3;
    sp3.addEdge("X", "Y", 1);
    sp3.addEdge("Y", "Z", -2);
    sp3.addEdge("Z", "X", -2); // total cycle weight -3 -> negative cycle
    cout << "--- Graph (negative-cycle demo) ---\n";
    sp3.printGraph();
    cout << "\n";
    sp3.bellmanFord("X");

    return 0;
}
