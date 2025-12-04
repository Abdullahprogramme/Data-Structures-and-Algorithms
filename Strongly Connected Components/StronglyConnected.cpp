#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class StronglyConnectedComponents {
    private:
        int nodes;
        vector<vector<int>> graph;

        vector<int> tin, low;
        vector<char> onstack;
        stack<int> st;
        int timer = 0;
        vector<vector<int>> components;

        void dfs(int v) {
            tin[v] = low[v] = ++timer;
            st.push(v);
            onstack[v] = 1;
            
            for (int to : graph[v]) {
                if (!tin[to]) {
                    dfs(to);
                    low[v] = min(low[v], low[to]);
                } else if (onstack[to]) {
                    low[v] = min(low[v], tin[to]);
                }
            }

            if (low[v] == tin[v]) {
                vector<int> cur;

                while (true) {
                    int u = st.top(); st.pop();
                    onstack[u] = 0;
                    cur.push_back(u);

                    if (u == v) break;
                }

                components.push_back(move(cur));
            }
        }

    public:
        explicit StronglyConnectedComponents(int nodes = 0) : nodes(nodes) {
            graph.assign(nodes + 1, {});
            tin.assign(nodes + 1, 0);
            low.assign(nodes + 1, 0);
            onstack.assign(nodes + 1, 0);
        }

        void addEdge(int u, int v) {
            if (u >= 1 && u <= nodes && v >= 1 && v <= nodes)
                graph[u].push_back(v);
        }

        void run() {
            for (int i = 1; i <= nodes; ++i)
                if (!tin[i]) dfs(i);
        }

        const vector<vector<int>>& getComponents() const { 
            return components; 
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    StronglyConnectedComponents scc(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        scc.addEdge(u, v);
    }

    scc.run();

    // Print only the components (one component per line)
    for (const auto &c : scc.getComponents()) {
        for (size_t i = 0; i < c.size(); ++i) {
            if (i) cout << ' ';
            cout << c[i];
        }
        
        cout << '\n';
    }

    return 0;
}
