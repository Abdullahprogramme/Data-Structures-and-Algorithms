#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <cassert>
#include <string>

using namespace std;

class EulerianCycle {
    private:
        Graph G;
        vector<int> next; // next[v] = index of next unused edge from v
        deque<int> cycle; // final Eulerian cycle (vertices)
        bool hasCycle;

        void buildCycle() {
            int V = G.V();
            next.assign(V, 0);

            // find start vertex: any with outdegree > 0, else 0
            int start = 0;
            for (int v = 0; v < V; ++v) if (G.getOutdegree(v) > 0) { start = v; break; }

            stack<int> st;
            st.push(start);

            while (!st.empty()) {
                int v = st.top();
                if (next[v] < (int)G.adj(v).size()) {
                    // still unused edges from v
                    int w = G.adj(v)[next[v]];
                    next[v]++;
                    st.push(w);
                } else {
                    // no more unused outgoing edges from v
                    cycle.push_front(v);
                    st.pop();
                }
            }

            // After traversal, verify that the cycle uses all edges (|cycle| == E+1)
            if ((int)cycle.size() != G.E() + 1) {
                hasCycle = false;
                cycle.clear();
            } else {
                hasCycle = true;
            }
        }

    public:
        EulerianCycle(const Graph& G_) : G(G_), next(), cycle(), hasCycle(false) {
            // 1. Check degree condition
            int V = G.V();
            for (int v = 0; v < V; ++v) {
                if (G.getIndegree(v) != G.getOutdegree(v)) {
                    hasCycle = false;
                    return;
                }
            }

            // 2. Build cycle using Hierholzer's algorithm
            buildCycle();
        }

        bool hasEulerianCycle() const { 
            return hasCycle; 
        }

        deque<int> getCycle() const {
            return cycle;
        }
};

// Validation function to help test the cycle
bool validateCycle(const Graph& G, const deque<int>& cycle, string &reason) {
    // empty cycle check
    if (cycle.empty()) {
        reason = "cycle empty";
        return false;
    }

    // all edges used check
    if ((int)cycle.size() != G.E() + 1) {
        reason = "cycle length != E+1";
        return false;
    }

    // first and last edge check
    if (cycle.front() != cycle.back()) {
        reason = "first and last vertices differ";
        return false;
    }

    // Count original edges (allowing parallel edges)
    map<pair<int,int>, int> orig;
    for (int v = 0; v < G.V(); ++v) {
        for (int w : G.adj(v)) orig[make_pair(v,w)]++;
    }

    // Count edges in cycle
    map<pair<int,int>, int> used;
    for (size_t i = 0; i + 1 < cycle.size(); ++i) {
        int from = cycle[i];
        int to = cycle[i + 1];
        used[make_pair(from, to)]++;
    }

    if (orig != used) {

        // find a mismatch to report
        for (auto &pair : orig) {
            auto edge = pair.first;
            int count = pair.second;

            int used_count = used[edge];
            if (count != used_count) {
                reason = "edge (" + to_string(edge.first) + "," + to_string(edge.second) + ") count mismatch: orig=" + to_string(count) + " used=" + to_string(used_count);
                return false;
            }
        }

        // check for extra used edges not in orig
        for (auto &pair : used) {
            if (orig.find(pair.first) == orig.end()) {
                reason = "used edge not in original: (" + to_string(pair.first.first) + "," + to_string(pair.first.second) + ")";
                return false;
            }
        }

        reason = "unknown mismatch between original edges and used edges";
        return false;
    }

    return true;
}

void printCycle(const deque<int>& cycle) {
    if (cycle.empty()) { 
        cout << "(none)\n"; 
        return; 
    }

    for (size_t i = 0; i < cycle.size(); ++i) {
        cout << (cycle[i] + 1);
        if (i + 1 < cycle.size()) cout << " -> ";
    }
    cout << '\n';
}

void Test(const string& name, const Graph& G) {
    cout << "--- " << name << " ---\n";
    cout << "V = " << G.V() << " and E = " << G.E() << '\n';

    EulerianCycle ec(G);
    if (!ec.hasEulerianCycle()) {
        cout << "No Eulerian cycle\n\n";
        return;
    }

    auto cycle = ec.getCycle();
    cout << "Found cycle: \n";
    printCycle(cycle);

    string reason;
    if (validateCycle(G, cycle, reason)) {
        cout << "Validation: PASS\n\n";
    } else {
        cout << "Validation: FAIL -> " << reason << "\n\n";
    }
}

int main() {
    // Test 1: Single vertex with self-loop
    {
        Graph G(1);
        G.addEdge(0, 0);
        Test("Single vertex, self-loop", G);
    }

    // Test 2: Complete directed graph K3 (all ordered pairs i != j)
    {
        int V = 3;
        Graph G(V);
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (i != j) G.addEdge(i, j);
        Test("Complete digraph K3 (no self-loops)", G);
    }

    // Test 3: Parallel edges between two vertices
    {
        Graph G(2);
        G.addEdge(0, 1);
        G.addEdge(0, 1);
        G.addEdge(0, 1);
        G.addEdge(1, 0);
        G.addEdge(1, 0);
        Test("Parallel edges 2-vertex graph", G);
    }

    // Test 4: No Eulerian cycle (unequal degrees)
    {
        Graph G(2);
        G.addEdge(0,1);
        Test("Unequal degrees (no cycle)", G);
    }

    // Test 5: Example from this lab
    {
        Graph G(7);
        
        // A: 1->2
        G.addEdge(0, 1);
        // B: 2->3
        G.addEdge(1, 2);
        // C: 3->4
        G.addEdge(2, 3);
        // D: 2->6
        G.addEdge(1, 5);
        // E: 6->7
        G.addEdge(5, 6);
        // F: 7->2
        G.addEdge(6, 1);
        // G: 4->5
        G.addEdge(3, 4);
        // H: 3->5
        G.addEdge(2, 4);
        // I: 5->1
        G.addEdge(4, 0);
        // J: 5->1 (parallel)
        G.addEdge(4, 0);
        // K: 1->3
        G.addEdge(0, 2);
        Test("Example from this lab", G);
    }

    return 0;
}