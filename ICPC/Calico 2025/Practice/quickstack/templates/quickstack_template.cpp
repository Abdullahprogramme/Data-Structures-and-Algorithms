#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * Output a possible configuration of the chest after performing quickstack
 * 
 * N: the number of items the player has
 * M: the number of items the chest has
 * P: the list of items on the player
 * C: the list of items in the chest
 */
void solve(int N, int M, vector<char> P, vector<char> C) {
    map<char, int> counts;
    for (char i : P) {
        counts[i]++;
    }
    for (char i : C) {
        counts[i]++;
    }

    vector<string> parts;
    for (auto [val, count] : counts) {
        parts.push_back(string(count, val));
    }

    // Join with spaces but not at the end
    for (int i = 0; i < parts.size(); ++i) {
        cout << parts[i];
        if (i == parts.size() - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M;
        cin >> N >> M;
        vector<char> P(N);
        for (char &item : P) {
            cin >> item;
        }
        vector<char> C(M);
        for (char &item : C) {
            cin >> item;
        }
        solve(N, M, P, C);
    }
}
