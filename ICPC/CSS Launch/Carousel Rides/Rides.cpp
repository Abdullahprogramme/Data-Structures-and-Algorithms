#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Rides.in", "r", stdin);
    freopen("Rides.out", "w", stdout);

    // Read test cases until "0 0"
    while (true) {
        int n, m;
        if (!(cin >> n >> m)) return 0;
        if (n == 0 && m == 0) break;

        int best_a = 0, best_b = 0;
        double best_ratio = 1e100;
        bool found = false;

        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            if (a > m) continue;               // ignore offers that require buying more than m tickets
            double ratio = double(b) / a;     // use floating-point division for price-per-ride

            // choose smaller ratio; on tie choose offer with more tickets
            if (!found ||
                ratio < best_ratio - 1e-12 ||
                (fabs(ratio - best_ratio) < 1e-12 && a > best_a)) {
                found = true;
                best_ratio = ratio;
                best_a = a;
                best_b = b;
            }
        }

        if (found) {
            cout << "Buy " << best_a << " tickets for $" << best_b << "\n";
        } else {
            cout << "No suitable tickets offered\n";
        }
    }

    return 0;
}