#include <iostream>

using namespace std;

/**
 * Return the appropriate text given the contest will start N minutes late.
 * 
 * N: the number of minutes late the contest will start
 */
string solve(int N) {
    if (N == 0) return "haha good one";
    else if (N > 0 && N <= 170) {
        int times = N / 10;
        string s;
        for (int i = 0; i < times; ++i) s += "berkeley";
        s += "time";
        return s;
    } else return "canceled";
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        cout << solve(N) << '\n';
    }
}
