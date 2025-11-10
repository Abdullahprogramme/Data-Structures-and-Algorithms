#include <iostream>
#include <vector>

using namespace std;

/**
  * NOTE: This template reads in values as int. You may want to change this for
  * bonus test sets.
  * 
  * Find the largest D digit number that does not contain any unlucky number
  * from L.
  *
  * N: the number of unlucky numbers
  * D: the number of digits in the number to find
  * L: the list of unlucky numbers
  */
int solve(int N, int D, vector<int> &L) {
    // YOUR CODE HERE
    return -1;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int N, D;
        cin >> N >> D;
        vector<int> L(N);
        for (int &L_i : L) {
            cin >> L_i;
        }
        cout << solve(N, D, L) << "\n";
    }
}
