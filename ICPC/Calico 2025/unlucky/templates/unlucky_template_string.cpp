#include <iostream>
#include <vector>

using namespace std;

/**
  * Find the largest D digit number that does not contain any unlucky number
  * from L.
  *
  * N: the number of unlucky numbers
  * D: the number of digits in the number to find
  * L: the list of unlucky numbers
  */
string solve(int N, int D, vector<string> &L) {
    // YOUR CODE HERE
    return "-1";
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int N, D;
        cin >> N >> D;
        vector<string> L(N);
        for (string &L_i : L) {
            cin >> L_i;
        }
        cout << solve(N, D, L) << "\n";
    }
}
