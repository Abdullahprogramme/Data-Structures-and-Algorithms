#include <iostream>
#include "digraph.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    ifstream in(argv[1]);
    Digraph G(in);
    cout << G.to_string();
}