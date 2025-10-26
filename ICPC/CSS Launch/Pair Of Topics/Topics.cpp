<<<<<<< HEAD
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Topics.in", "r", stdin);
    freopen("Topics.out", "w", stdout);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    int pairs = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] + a[j] > b[i] + b[j]) {
                ++pairs;
            }
        }
    }

    cout << pairs << "\n";

    return 0;
}
=======
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Topics.in", "r", stdin);
    freopen("Topics.out", "w", stdout);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    int pairs = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] + a[j] > b[i] + b[j]) {
                ++pairs;
            }
        }
    }

    cout << pairs << "\n";

    return 0;
}
>>>>>>> 856627f9fb38d9eb137e600c81d373364930179f
