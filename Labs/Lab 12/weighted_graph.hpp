#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <vector>

using namespace std;

class Edge {
    int _v;
    int _w;
    double _weight;

    public:
        Edge(int v, int w, double weight) : _v{v}, _w{w}, _weight{weight} {}
        
        int either() const {
            return _v;
        }

        int other(int vertex) const {
            if (vertex == _v) return _w;
            else return _v;
        }

        double weight() const {
            return _weight;
        }

        bool operator<(const Edge& that) const {
            return this->_weight < that._weight;
        }
};

class EdgeWeightedGraph {
    vector<forward_list<Edge>> _adj;
    vector<int> _degree;
    int _E;

    private:
        void validateVertex(int v) const {
            if (v < 0 || v >= V())
                throw invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string((V()-1)));
        }

    public:
        EdgeWeightedGraph(int n) : _adj(n), _degree(n), _E{0} {}

        EdgeWeightedGraph(istream& in) : _E{0} {
            int V, E;
            in >> V >> E;

            if (V < 0 || E < 0) 
                throw invalid_argument("number of vertices and edges in a Graph must be non-negative");

            _adj.resize(V);
            _degree.resize(V);

            for (int i = 0; i < E; i++) {
                int u, v;
                double weight;
                in >> u >> v >> weight;
                addEdge(u, v, weight);
            }
        }


        int V() const {
            return _adj.size();
        }

        int E() const {
            return _E;
        }

        void addEdge(const Edge& e) {
            int v = e.either();
            int w = e.other(v);
            validateVertex(v);
            validateVertex(w);
            _adj[v].push_front(e);
            _adj[w].push_front(e);
            _E++;
            _degree[v]++;
            _degree[w]++;
        }

        void addEdge(int v, int w, double weight) {
            addEdge(Edge{v, w, weight});
        }

        const forward_list<Edge>& adj(int v) const {
            validateVertex(v);
            return _adj[v];
        }

        int degree(int v) const {
            validateVertex(v);
            return _degree[v];
        }

        vector<Edge> edges() const {
            vector<Edge> list;
            list.reserve(E());

            for (int v = 0; v < V(); v++) {
                for (Edge e : adj(v)) {
                    // add only one direction to avoid duplicates, and ignore self-loops
                    if (e.other(v) > v) {
                        list.push_back(e);
                    }
                }
            }

            return list;
        }

        string to_string() {
            string s; 
            s.append(std::to_string(V()) + " vertices, " + std::to_string(_E) + " edges " + "\n");

            for (int v = 0; v < V(); v++) {
                s.append(std::to_string(v) + ": ");

                for (Edge w : _adj[v]) {
                    s.append(std::to_string(w.other(v)) + "(" + std::to_string(w.weight()) + ") ");
                }
                s.append("\n");
            }

            return s;
        }

};
