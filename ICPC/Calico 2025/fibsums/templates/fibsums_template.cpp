#include <iostream>
#include <vector>

using namespace std;

/**
 * Output the resulting array A_1, A_2, ... , A_N after
 * all fib-queries have completed.
 * 
 * N: the length of the array A_1, A_2, ... , A_N
 * Q: the number of fib-queries
 * L: the list of L_i values involved with each fib-query
 * R: the list of R_i values involved with each fib-query
 */
void solve(int N, int Q, vector<int> L, vector<int> R) {
    // YOUR CODE HERE
    return;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, Q;
        cin >> N >> Q;
        vector<int> L(Q);
        vector<int> R(Q);
        for (int j = 0; j < Q; ++j) {
            cin >> L[j] >> R[j];
        }
        solve(N, Q, L, R);
    }
}
