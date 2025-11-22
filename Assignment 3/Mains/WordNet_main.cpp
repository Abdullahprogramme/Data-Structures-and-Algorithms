#include "./Digraph.hpp"
#include "./ShortestCommonAncestor.hpp"

#include <random>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " n m\n";
        return 1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    if (n <= 0 || m <= 0) { 
        cerr << "n and m must be positive\n"; return 1; 
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, m);

    vector<int> pathsA(n), pathsB(n);
    for (int i = 0; i < n; ++i) pathsA[i] = dist(gen);
    for (int i = 0; i < n; ++i) pathsB[i] = dist(gen);

    long long SA = 0, SB = 0;
    SA = accumulate(pathsA.begin(), pathsA.end(), SA);
    SB = accumulate(pathsB.begin(), pathsB.end(), SB);

    int totalV = (int)(SA + SB + 1);
    Digraph G(totalV);

    const int root = 0;
    int next = 1; // next available vertex id
    vector<int> subsetA, subsetB;

    auto addPath = [&](int len, vector<int>& subset) {
        // len >=1
        int start = next++;
        int current = start;
        if (len == 1) {
            G.addEdge(start, root);
        } else {
            for (int j = 1; j <= len-1; ++j) {
                int v = next++;
                G.addEdge(current, v);
                current = v;
            }
            G.addEdge(current, root);
        }

        subset.push_back(start);
    };

    for (int x : pathsA) addPath(x, subsetA);
    for (int x : pathsB) addPath(x, subsetB);

    // Construct SCA
    ShortestCommonAncestor sca(G);
    int result = sca.lengthSubset(subsetA, subsetB);

    int expect = *min_element(pathsA.begin(), pathsA.end()) + *min_element(pathsB.begin(), pathsB.end());

    if (result != expect) {
        cout << "Error! expected " << expect << " got " << result << "\n";
        return 2;
    }
    cout << "OK: result=" << result << " expected=" << expect << "\n";
    return 0;
}
