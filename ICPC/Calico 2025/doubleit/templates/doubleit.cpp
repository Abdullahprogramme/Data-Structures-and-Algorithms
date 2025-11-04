#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Return the total money Big Ben pays
 *
 * N: length of the string P
 * P: String representing the people Big Ben talks to
 */
int solve(int N, string P) {
    int total = 0;
    int dollar = 1;

    for (auto ch : P) {
        if (ch == 'D') dollar *= 2;
        else {
            total += dollar;
            dollar = 1;
        } 
    }

    return total;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N;
        string P;
        cin >> N;
        cin >> P;
        cout << solve(N, P) << '\n';
    }
}
