#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <forward_list>
#include <stdexcept>

using namespace std;

class Digraph {
    vector<forward_list<int>> _adj;
    vector<int> _indegree;
    vector<int> _outdegree;
    int _E;

public:
    Digraph(int n) : _adj(n), _indegree(n), _outdegree(n), _E{0} {}

    Digraph(istream& in) : _E{0} {
        int V, E;
        in >> V >> E;
        if (V < 0 || E < 0) 
            throw new invalid_argument("number of vertices and edges in a Graph must be non-negative");
        _adj.resize(V);
        _indegree.resize(V);
        _outdegree.resize(V);
        for (int i = 0; i < E; i++) {
            int v, w;
            in >> v >> w;
            validateVertex(v);
            validateVertex(w);
            addEdge(v, w);
        }
    }

    int V() const {
        return _adj.size();
    }
    
    int E() const {
        return _E;
    }

    void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        _adj[v].push_front(w);
        _outdegree[v]++;
        _indegree[w]++;
        _E++;
    }

    const forward_list<int>& adj(int v) const {
        validateVertex(v);
        return _adj[v];
    }

    int indegree(int v) const {
        validateVertex(v);
        return _indegree[v];
    }

    int outdegree(int v) const {
        validateVertex(v);
        return _outdegree[v];
    }

    string to_string() const {
        string s; 
        s.append(std::to_string(V()) + " vertices, " + std::to_string(_E) + " edges " + "\n");
        for (int v = 0; v < V(); v++) {
            s.append(std::to_string(v) + ": ");
            for (int w : _adj[v]) {
                s.append(std::to_string(w) + " ");
            }
            s.append("\n");
        }
        return s;
    }

    Digraph reverse() const {
        Digraph r(V());
        for(int v=0; v<V(); v++) {
            for(int w : adj(v)) {
                r.addEdge(w,v);
            }
        }
        return r;
    }

private:
    void validateVertex(int v) const {
        if (v < 0 || v >= V())
            throw new invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string((V()-1)));
    }

};


