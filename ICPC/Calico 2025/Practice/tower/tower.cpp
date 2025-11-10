#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

long long helper(vector<int>& P, vector<int>& D, int start, int N) {
    vector<bool> visited(N, false);
    long long time = 0;
    int current = start;
    long long herry_power = 0;

    // wait at the every tower after reaching if P[i] > herry_power
    while (true) {
        
        visited[current] = true;
        // cout << "Visiting tower " << current << " with power " << herry_power << " at time " << time << endl;

        if (P[current] > herry_power) {
            time += P[current] - herry_power;
            herry_power += P[current];
        }

        if (visited[(current + 1) % N]) {
            // cout << "Cycle detected, returning large time." << endl;
            return time;
        }

        herry_power += D[current];
        time += D[current]; // move to next tower

        // cout << "herry_power after tower " << current << " = " << herry_power << endl;
        current = (current + 1) % N;
    }
}


void solve(int N, vector<int>& P, vector<int>& D) {
    if (P.size() == 0 || D.size() == 0) {
        cout << 0 << endl;
        return;
    }

    long long best_time = LLONG_MAX;
    for (int i = 0; i < N; i++) {

        best_time = min(best_time, helper(P, D, i, N));

        // cout << endl;
    }

    cout << best_time << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        vector<int> P(N);
        for (int j = 0; j < N; j++) {
            cin >> P[j];
        }
        vector<int> D(N);
        for (int j = 0; j < N; j++) {
            cin >> D[j];
        }

        solve(N, P, D);
    }
}
