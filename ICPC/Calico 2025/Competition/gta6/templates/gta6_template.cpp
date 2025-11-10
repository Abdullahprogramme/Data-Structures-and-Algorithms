#include <iostream>

using namespace std;
int Y_0 = 2026;
int M_0 = 11;
int D_0 = 19;

/**
 * E: Name of event
 * Y: Year of event
 * M: Month of event
 * D: Day of event
 */
 string solve(string E, int Y, int M, int D) {
    // YOUR CODE HERE
    string before = "we got " + E + " before gta6";
    string after = "we got gta6 before " + E;

    return (Y < Y_0 || (Y == Y_0 && M < M_0) || (Y == Y_0 && M == M_0 && D < D_0) ? before : after;
}

int main() {
    int T;
    cin >> T;
    cin.ignore();
    for (int i = 0; i < T; i++) {
        string E;
        getline(cin, E);
        int D, M, Y;
        cin >> Y >> M >> D;
        cin.ignore();
        cout << solve(E, Y, M, D) << '\n';
    }
}