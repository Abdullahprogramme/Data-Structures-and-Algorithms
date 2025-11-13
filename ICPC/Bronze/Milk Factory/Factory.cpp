#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void dfs(int node, unordered_map<int, vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Factory.in", "r", stdin);
    freopen("Factory.out", "w", stdout);

    int N;
    cin >> N;
    // Question: find node i such that from every node j (j != i) there is a path to i
    unordered_map<int, vector<int>> adj;
    for (int i = 0; i < N - 1; ++i) {
        int A, B;
        cin >> A >> B;
        adj[A].push_back(B);
    }



    return 0;
}
