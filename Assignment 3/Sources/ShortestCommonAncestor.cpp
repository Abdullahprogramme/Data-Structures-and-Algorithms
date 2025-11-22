#include "./ShortestCommonAncestor.hpp"
#include <queue>
#include <stdexcept>
#include <limits>

using namespace std;

static bool hasCycleUtil(const Digraph& G, int v, vector<int>& color) {
    color[v] = 1; // visiting

    for (int w : G.adj(v)) {
        if (color[w] == 1) return true;
        if (color[w] == 0 && hasCycleUtil(G, w, color)) return true;
    }

    color[v] = 2; // visited
    return false;
}

static bool hasCycle(const Digraph& G) {
    int n = G.V();
    vector<int> color(n, 0);

    // states: 0=unvisited, 1=visiting, 2=visited
    for (int v = 0; v < n; ++v) if (color[v] == 0) if (hasCycleUtil(G, v, color)) return true;
    return false;
}

ShortestCommonAncestor::ShortestCommonAncestor(const Digraph& g) : G(g) {
    // Validate rooted DAG: no cycle
    if (hasCycle(G)) throw invalid_argument("Graph has a cycle");

    // exactly one root: vertex with outdegree 0
    auto outdeg = G.outdegreeCount();
    int roots = 0;
    int rootIdx = -1;

    for (int v = 0; v < (int)outdeg.size(); ++v) {
        if (outdeg[v] == 0) { 
            roots++; 
            rootIdx = v; 
        }
    }

    if (roots != 1) throw invalid_argument("Graph must have exactly one root");

    // check that root is ancestor of all vertices -> reverse graph BFS from root visits all
    Digraph R = G.reverse();
    vector<char> seen(G.V(), 0);
    queue<int> q;

    q.push(rootIdx); 
    seen[rootIdx] = 1; 
    int count = 1;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : R.adj(v)) 
            if (!seen[w]) { 
                seen[w] = 1; 
                q.push(w); 
                ++count; 
            }
    }

    if (count != G.V()) throw invalid_argument("Root is not reachable from all vertices");
}

void ShortestCommonAncestor::validateVertex(int v) const {
    if (v < 0 || v >= G.V()) throw invalid_argument("vertex out of range");
}

vector<int> ShortestCommonAncestor::bfsFromSources(const vector<int>& sources) const {
    if (sources.empty()) throw invalid_argument("empty source set");

    vector<int> dist(G.V(), -1);
    queue<int> q;

    for (int s : sources) {
        validateVertex(s);
        if (dist[s] == -1) { 
            dist[s] = 0; 
            q.push(s); 
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : G.adj(v)) {
            if (dist[w] == -1) { 
                dist[w] = dist[v] + 1; 
                q.push(w); 
            }
        }
    }

    return dist;
}

int ShortestCommonAncestor::lengthSubset(const vector<int>& subsetA, const vector<int>& subsetB) const {
    if (subsetA.empty() || subsetB.empty()) throw invalid_argument("empty subset");

    auto distA = bfsFromSources(subsetA);
    auto distB = bfsFromSources(subsetB);

    int best = numeric_limits<int>::max();

    for (int v = 0; v < G.V(); ++v) {
        if (distA[v] >= 0 && distB[v] >= 0) {
            int s = distA[v] + distB[v];
            if (s < best) best = s;
        }
    }

    if (best == numeric_limits<int>::max()) return -1;
    return best;
}

int ShortestCommonAncestor::ancestorSubset(const vector<int>& subsetA, const vector<int>& subsetB) const {
    if (subsetA.empty() || subsetB.empty()) throw invalid_argument("empty subset");

    auto distA = bfsFromSources(subsetA);
    auto distB = bfsFromSources(subsetB);

    int best = numeric_limits<int>::max();
    int best_v = -1;

    for (int v = 0; v < G.V(); ++v) {
        if (distA[v] >= 0 && distB[v] >= 0) {
            int s = distA[v] + distB[v];
            if (s < best) { 
                best = s; 
                best_v = v; 
            }
        }
    }

    return best_v;
}

int ShortestCommonAncestor::length(int v, int w) const {
    validateVertex(v); validateVertex(w);

    vector<int> a{v}; vector<int> b{w};
    return lengthSubset(a,b);
}

int ShortestCommonAncestor::ancestor(int v, int w) const {
    validateVertex(v); validateVertex(w);
    
    vector<int> a{v}; vector<int> b{w};
    return ancestorSubset(a,b);
}
