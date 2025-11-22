#pragma once

#include "Digraph.hpp"
#include <vector>

using namespace std;

class ShortestCommonAncestor {
    private:
        Digraph G; // rooted DAG

        void validateVertex(int v) const;
        vector<int> bfsFromSources(const vector<int>& sources) const;

    public:
        // Constructor takes a digraph (must be a rooted DAG)
        ShortestCommonAncestor(const Digraph& G);

        int length(int v, int w) const;
        int ancestor(int v, int w) const;
        int lengthSubset(const vector<int>& subsetA, const vector<int>& subsetB) const;
        int ancestorSubset(const vector<int>& subsetA, const vector<int>& subsetB) const;
};
