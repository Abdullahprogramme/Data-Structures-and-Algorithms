#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Blocks.in", "r", stdin);
    freopen("Blocks.out", "w", stdout);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    unordered_map<int, int> segments;
    int total_segments = 0;

    for (int i = 0; i < n; ++i) {
        if (i == 0 || a[i] != a[i - 1]) {
            segments[a[i]]++;
            total_segments++;
        }
    }

    int unique_values = segments.size();
    int difficulty = total_segments - unique_values;

    cout << difficulty << "\n";
    return 0;
}
