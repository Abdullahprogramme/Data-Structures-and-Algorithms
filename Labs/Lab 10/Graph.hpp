#pragma once

#include <vector>
#include <stdexcept>

using namespace std;

// Directed graph
class Graph {
    private:
        int _V; // number of vertices
        int _E; // number of edges
        vector<vector<int>> _adj; // adjacency lists
        vector<int> _indegree; // degree of each vertex

    public:
        Graph(int V = 0) : _V(V), _E(0), _adj(V), _indegree(V, 0) {}

        int V() const { 
            return _V; 
        }

        int E() const { 
            return _E; 
        }

        // Add a directed edge from 'from' to 'to'
        void addEdge(int from, int to) {
            if (from < 0 || from >= _V || to < 0 || to >= _V) {
                throw out_of_range("vertex out of range");
            }
            
            _adj[from].push_back(to);
            _indegree[to]++;
            _E++;
        }

        // Get adjacency list of vertex v
        const vector<int>& adj(int v) const {
            return _adj[v];
        }

        // Get all adjacency lists
        const vector<vector<int>>& adj() const { 
            return _adj; 
        }

        int getIndegree(int v) const { 
            return _indegree[v]; 
        }

        int getOutdegree(int v) const { 
            return adj(v).size();
        }
};