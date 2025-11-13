#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// DFS approach to topological sorting
void DFS_topological_sort(const unordered_map<string, vector<string>> &graph, const string &node, unordered_set<string> &visited, vector<string> &result) {
    visited.insert(node);

    auto it = graph.find(node);
    if (it != graph.end()) {
        for (const auto &neighbor : it->second) {
            if (visited.find(neighbor) == visited.end()) {
                DFS_topological_sort(graph, neighbor, visited, result);
            }
        }
    }

    result.push_back(node);
}

vector<string> topological_sort(const unordered_map<string, vector<string>> &graph) {
    unordered_set<string> visited;
    vector<string> result;

    for (const auto &pair : graph) {
        const string &node = pair.first;
        if (visited.find(node) == visited.end()) {
            DFS_topological_sort(graph, node, visited, result);
        }
    }

    reverse(result.begin(), result.end());
    return result;
}

// Kahn's algorithm for topological sorting
vector<string> kahn_topological_sort(const unordered_map<string, vector<string>> &graph) {

    // 1. Compute in-degrees of all nodes
    unordered_map<string, int> in_degree;
    for (const auto &pair : graph) {
        const string &node = pair.first;
        if (in_degree.find(node) == in_degree.end()) {
            in_degree[node] = 0;
        }
        for (const auto &neighbor : pair.second) {
            in_degree[neighbor]++;
        }
    }

    // 2. Collect nodes with in-degree of 0
    vector<string> zero_in_degree;
    for (const auto &pair : in_degree) {
        if (pair.second == 0) {
            zero_in_degree.push_back(pair.first);
        }
    }

    // 3. Process nodes with in-degree of 0
    vector<string> result;
    while (!zero_in_degree.empty()) {
        string node = zero_in_degree.back();
        zero_in_degree.pop_back();
        result.push_back(node);

        auto it = graph.find(node);
        if (it != graph.end()) {
            for (const auto &neighbor : it->second) {
                in_degree[neighbor]--;
                if (in_degree[neighbor] == 0) {
                    zero_in_degree.push_back(neighbor);
                }
            }
        }
    }

    // 4. Check for cycles
    if (result.size() != graph.size()) {
        // Graph has at least one cycle
        return {};
    }

    return result;
}

int main() {
    unordered_map<string, vector<string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"D"}},
        {"C", {"D"}},
        {"D", {"E"}},
        {"E", {}}
    };

    cout << "Topological Sort (DFS): ";
    auto dfs_result = topological_sort(graph);
    for (const auto &node : dfs_result) {
        cout << node << " ";
    }
    cout << "\n";

    cout << "Topological Sort (Kahn's Algorithm): ";
    auto kahn_result = kahn_topological_sort(graph);
    for (const auto &node : kahn_result) {
        cout << node << " ";
    }
    cout << "\n";

    return 0;
}