#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("MadeUp.in", "r", stdin);
    freopen("MadeUp.out", "w", stdout);

    int N;
    cin >> N;
    vector<int> A(N), B(N), C(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    for (int i = 0; i < N; ++i) cin >> C[i];

    unordered_map<int, int> countA;
    for (int i = 0; i < N; ++i) {
        countA[A[i]]++;
    }

    unordered_map<int, int> countBC;
    for (int j = 0; j < N; ++j) {
        int idx = C[j] - 1;
        countBC[B[idx]]++;
    }

    long long total_pairs = 0;
    for (const auto& [v, cntA] : countA) {
        total_pairs += 1LL * cntA * countBC[v];
    }

    cout << total_pairs << '\n';
    return 0;
}
