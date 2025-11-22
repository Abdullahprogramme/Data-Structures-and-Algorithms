#include "./Digraph.hpp"
#include <stdexcept>

using namespace std;

Digraph::Digraph(int V) : _adj(V), _E(0) {}

void Digraph::addEdge(int v, int w) {
    if (v < 0 || v >= (int)_adj.size() || w < 0 || w >= (int)_adj.size()) {
        throw out_of_range("vertex out of range");
    }

    _adj[v].push_back(w);
    ++_E;
}

int Digraph::V() const { 
    return (int)_adj.size(); 
}

int Digraph::E() const { 
    return _E; 
}

const vector<int>& Digraph::adj(int v) const {
    if (v < 0 || v >= (int)_adj.size()) throw out_of_range("vertex out of range");
    return _adj[v];
}

vector<int> Digraph::outdegreeCount() const {
    vector<int> out(_adj.size());
    for (size_t i = 0; i < _adj.size(); ++i) out[i] = (int)_adj[i].size();

    return out;
}

Digraph Digraph::reverse() const {
    Digraph R(V());

    for (int v = 0; v < V(); ++v) {
        for (int w : _adj[v]) R.addEdge(w, v);
    }
    
    return R;
}
