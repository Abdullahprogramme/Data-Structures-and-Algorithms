#include "./Digraph.hpp"
#include "./ShortestCommonAncestor.hpp"
#include <iostream>

using namespace std;

int main() {
    // Digraph:
    // 0 -> 3 -> 5
    // 1 -> 3
    // 2 -> 4 -> 5
    // root = 5
    Digraph G(6);
    G.addEdge(0, 3);
    G.addEdge(1, 3);
    G.addEdge(2, 4);
    G.addEdge(3, 5);
    G.addEdge(4, 5);

    try {
        ShortestCommonAncestor sca(G);
        int len01 = sca.length(0, 1); // expect 2 (0 -> 3 + 1 -> 3)
        int anc01 = sca.ancestor(0, 1); // expect 3
        int len02 = sca.length(0, 2); // expect 4 (0 -> 3 -> 5 and 2 -> 4 -> 5 => 2 + 2)
        int anc02 = sca.ancestor(0, 2); // expect 5

        bool ok = true;
        if (len01 != 2) { cerr << "len01 expected 2 got " << len01 << '\n'; ok = false; }
        if (anc01 != 3) { cerr << "anc01 expected 3 got " << anc01 << '\n'; ok = false; }
        if (len02 != 4) { cerr << "len02 expected 4 got " << len02 << '\n'; ok = false; }
        if (anc02 != 5) { cerr << "anc02 expected 5 got " << anc02 << '\n'; ok = false; }

        if (ok) { 
            cout << "SCA tests passed\n"; 
            return 0; 
        }
        else { 
            cout << "SCA tests failed\n"; 
            return 2; 
        }
        
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << '\n';
        return 3;
    }
}
