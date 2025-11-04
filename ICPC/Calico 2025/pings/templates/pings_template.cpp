#include <iostream>
#include <vector>

using namespace std;

/**
  * Output the number of times each user is pinged in the server after
  * all actions.
  * 
  * Q: the total number of actions
  * N: the number of roles in the server
  * M: the number of users in the server
  * X: the list of actions performed at each timestep
  * R: the list of roles involved at each timestep
  * U: the list of users involved at each timestep, or -1 if the action is a ping
  */
void solve (int Q, int N, int M, vector<char> X, vector<int> R, vector<int> U) {
    // YOUR CODE HERE
}

int main () {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int Q, N, M;
        cin >> Q >> N >> M;
        vector<char> X(Q);
        vector<int> R(Q);
        vector<int> U(Q);
        for (int j = 0; j < Q; ++j) {
            cin >> X[j];
            if (X[j] == 'P') {
                cin >> R[j];
                U[j] = -1;
            }
            else {
                cin >> R[j] >> U[j];
            }
        }
        solve(Q, N, M, X, R, U);
    }
}