#include <iostream>
#include <fstream>
#include <iomanip>
#include "weighted_graph.hpp"
#include "boruvka_mst.hpp"

using namespace std;

int main() {
    ifstream file("tinyEWG.txt");
    EdgeWeightedGraph G(file);
    
    cout << "Graph:\n" << G.to_string() << "\n";
    
    BoruvkaMST boruvka(G);
    
    cout << fixed << setprecision(5);
    cout << "Boruvka MST weight: " << boruvka.weight() << "\n";
    
    cout << "\nBoruvka MST edges:\n";
    for (const Edge& e : boruvka.edges()) {
        int v = e.either();
        cout << v << "-" << e.other(v) << " " 
                  << e.weight() << "\n";
    }
    
    return 0;
}
