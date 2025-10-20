#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Construction.in", "r", stdin);
    freopen("Construction.out", "w", stdout);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int n;
        cin >> n;
        vector<int> ans(2*n, 0);

        for (int x = n; x >= 1; --x) {
            bool placed = false;
            for (int p = 0; p < 2*n && !placed; ++p) {
                if (ans[p] != 0) continue;
                for (int q = p + x; q < 2*n; q += x) {
                    if (ans[q] == 0) {
                        ans[p] = ans[q] = x;
                        placed = true;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < 2*n; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
