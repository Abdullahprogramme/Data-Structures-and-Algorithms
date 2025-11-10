#include <iostream>
#include <vector>

using namespace std;

/**
 * Output the true difficulty of each trail given
 * a mountain range with N checkpoints and M trails
 * between them.
 * 
 * N: the number of checkpoints on the mountain
 * M: the number of available trails between checkpoints
 * X: the list of X_i, the checkpoints at the start of each trail
 * Y: the list of Y_i, the checkpoints at the end of each trail
 * Z: the list of Z_i, the skill levels needed to traverse each trail
 */
void solve(int N, int M, vector<int> X, vector<int> Y, vector<int> Z) {
    // YOUR CODE HERE
    return;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M;
        cin >> N >> M;
        vector<int> X(M);
        vector<int> Y(M);
        vector<int> Z(M);
        for (int j = 0; j < M; j++) {
            cin >> X[j] >> Y[j] >> Z[j];
        }
        solve(N, M, X, Y, Z);
    }
}
