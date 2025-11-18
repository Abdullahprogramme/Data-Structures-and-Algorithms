#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> kahn_topological_sort(const unordered_map<int, vector<int>> &graph) {

    // 1. Compute in-degrees of all nodes
    unordered_map<int, int> in_degree;
    for (const auto &pair : graph) {
        const int &node = pair.first;
        if (in_degree.find(node) == in_degree.end()) {
            in_degree[node] = 0;
        }
        for (const auto &neighbor : pair.second) {
            in_degree[neighbor]++;
        }
    }

    // 2. Collect nodes with in-degree of 0
    vector<int> zero_in_degree;
    for (const auto &pair : in_degree) {
        if (pair.second == 0) {
            zero_in_degree.push_back(pair.first);
        }
    }

    // 3. Process nodes with in-degree of 0
    vector<int> result;
    while (!zero_in_degree.empty()) {
        int node = zero_in_degree.back();
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
    unordered_map<int, vector<int>> graph = {
        {5, {2, 0}},
        {4, {0, 1}},
        {3, {1}},
        {2, {3}},
        {1, {}},
        {0, {}}
    };

    vector<int> sorted_nodes = kahn_topological_sort(graph);

    if (sorted_nodes.empty()) {
        cout << "Graph has at least one cycle." << endl;
    } else {
        cout << "Topological Sort: ";
        for (int node : sorted_nodes) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}