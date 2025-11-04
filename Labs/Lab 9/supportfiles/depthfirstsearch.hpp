#pragma once

#include <vector>
#include <algorithm>
#include "graph.hpp"

using namespace std;

class DepthFirstSearch {
    vector<bool> marked;
    vector<int> edgeTo;
    int s;

    DepthFirstSearch(const Graph& G, int _s) : marked(G.V(), false) , edgeTo(G.V(), -1), s(_s) {
        dfs(G, s);
    }

    bool isConnected(int v) const {
        return marked[v];
    }

    vector<int> pathTo(int v) {
        vector<int> path;
        if (!marked[v]) return path;
        for (int x = v; x != s; x = edgeTo[x])
            path.push_back(x);
        path.push_back(s);
        reverse(path.begin(), path.end());
        return path;
    }

private:
    void dfs(const Graph& G, int v) {
        marked[v] = true;
        for (int w : G.adj(v))
            if (!marked[w]) {
                dfs(G, w);
                edgeTo[w] = v;
            }
    }
};
