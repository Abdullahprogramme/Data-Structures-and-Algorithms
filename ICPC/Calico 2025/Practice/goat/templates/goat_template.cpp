#include <iostream>
#include <vector>

using namespace std;

/**
 * Given a rooted tree, with each vertex labeled A_1, A_2, .., A_N,
 * find the result of all Q GOAT queries.
 * 
 * N: the size of the tree
 * Q: the number of GOAT queries
 * P: the list of parent nodes for each vertex
 * A: the list of labels on the vertices of the tree
 * G: the list of each GOAT query
 */
void solve(int N, int Q, vector<int> P, vector<int> A, vector<int> G) {
    // YOUR CODE HERE
    return;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, Q;
        cin >> N >> Q;
        vector<int> P(N);
        for (int &item : P) {
            cin >> item;
        }
        vector<int> A(N);
        for (int &item : A) {
            cin >> item;
        }
        vector<int> G(Q);
        for (int &item : G) {
            cin >> item;
        }
        solve(N, Q, P, A, G);
    }
}
