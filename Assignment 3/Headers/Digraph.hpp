#pragma once

#include <vector>

using namespace std;

class Digraph {
    private:
        vector<vector<int>> _adj;
        int _E = 0;

    public:
        Digraph(int V = 0);

        void addEdge(int v, int w);
        int V() const;
        int E() const;
        
        const vector<int>& adj(int v) const;
        vector<int> outdegreeCount() const;
        Digraph reverse() const;
};