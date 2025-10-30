#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Topics.in", "r", stdin);
    freopen("Topics.out", "w", stdout);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = a[i] - b[i];

    sort(c.begin(), c.end());
    int pairs = 0;
    for (int i = 0; i < n; ++i) {
        // find first element > -c[i] in range (i, n)
        auto it = upper_bound(c.begin() + i + 1, c.end(), -c[i]);
        pairs += (c.end() - it);
    }

    cout << pairs << "\n";
    return 0;
}
