#pragma once

#include <vector>
#include <algorithm>
#include "digraph.hpp"

using namespace std;

class DirectedDFS {
    vector<bool> marked;
    vector<int> edgeTo;
    int s;

    DirectedDFS(const Digraph &G, int _s) : marked(G.V(), false) , edgeTo(G.V(), -1), s(_s) {
        dfs(G, s);
    }

    bool isReachable(int v) const {
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
    void dfs(const Digraph &G, int v) {
        marked[v] = true;
        for (int w : G.adj(v))
            if (!marked[w]) {
                dfs(G, w);
                edgeTo[w] = v;
            }
    }
};
