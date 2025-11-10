#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/**
 * Return the top-down area of the shape
 *   
 *  N: number of rows
 *  M: number of columns
 *  G: an N by M grid representing the front-view and depths of the character
 */
int solve(int N, int M, vector<string> G) {
    // YOUR CODE HERE
    vector<int> result(M, 0);

    for (auto row : G) {
        for (int i = 0; i < row.size(); i++) {
            if (row[i] == '.') row[i] = '0';

            result[i] = max(result[i], int(row[i] - '0'));
        }
    }


    return accumulate(result.begin(), result.end(), 0);
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M;
        cin >> N >> M;
        vector<string> G;
        for (int j = 0; j < N; j++) {
            string row; cin >> row;
            G.push_back(row);
        }
        cout << solve(N, M, G) << '\n';
    }
}
