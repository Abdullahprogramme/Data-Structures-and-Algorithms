#pragma once

#include <vector>
#include <algorithm>
#include <limits>
#include "weighted_graph.hpp"
#include "union_find.hpp"

using namespace std;

class BoruvkaMST {
    vector<Edge> mst;
    double totalWeight;

    public:
        BoruvkaMST(const EdgeWeightedGraph& G) : totalWeight(0.0) {
            // TODO: Implement Boruvka's algorithm
            // Hint structure:
            // 1. Initialize union-find for V vertices
            // 2. While number of components > 1:
            //    a. Find cheapest edge for each component
            //    b. Add all valid edges to MST
            //    c. Update union-find

            UnionFind uf(G.V());
            int numComponents = G.V();

            int instrumentationCount = 0; // For phase analysis
            while (numComponents > 1) {
                vector<Edge> cheapest(G.V(), Edge(-1, -1, numeric_limits<double>::infinity()));

                // Phase 1: Find cheapest edge for each component
                for (const Edge& e : G.edges()) {
                    int v = e.either();
                    int w = e.other(v);
                    int setV = uf.find(v);
                    int setW = uf.find(w);

                    if (setV != setW) {
                        // Check if this edge is the cheapest for setV
                        if (e.weight() < cheapest[setV].weight()) {
                            cheapest[setV] = e;
                        }

                        // Check if this edge is the cheapest for setW
                        if (e.weight() < cheapest[setW].weight()) {
                            cheapest[setW] = e;
                        }
                    }
                }

                // Phase 2: Add cheapest edges to MST
                for (int i = 0; i < G.V(); i++) {
                    Edge e = cheapest[i];
                    
                    if (e.either() != -1) {
                        int v = e.either();
                        int w = e.other(v);
                        int setV = uf.find(v);
                        int setW = uf.find(w);

                        if (setV != setW) {
                            uf.unify(setV, setW);
                            mst.push_back(e);
                            totalWeight += e.weight();
                            numComponents--;
                        }
                    }
                }

                instrumentationCount++; // Increment phase count
            }

            cout << "Total instrumentation count (phases): " << instrumentationCount << "\n";
        }

        const vector<Edge>& edges() const {
            return mst;
        }

        double weight() const {
            return totalWeight;
        }

        bool isValid(const EdgeWeightedGraph& G) const {
            return mst.size() == G.V() - 1;
        }
};
