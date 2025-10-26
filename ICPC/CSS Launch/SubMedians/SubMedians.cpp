#include <iostream>
#include <vector>

using namespace std;

bool can(int v, vector<int> &a, int k, int &L, int &R) {
    int n = a.size();
    vector<int> pref(n + 1, 0);
    int minPref = 0, minIndex = 0;

    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (a[i - 1] >= v ? 1 : -1);

        if (i >= k) {
            if (pref[i] - minPref >= 0) {
                L = minIndex + 1;
                R = i;
                return true;
            }
        }

        if (i - k + 1 >= 0 && pref[i - k + 1] < minPref) {
            minPref = pref[i - k + 1];
            minIndex = i - k + 1;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("SubMedians.in", "r", stdin);
    freopen("SubMedians.out", "w", stdout);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int low = 1, high = n, vmax = 1, L = 1, R = k;
        while (low <= high) {
            int mid = (low + high) / 2;
            int ltemp, rtemp;
            if (can(mid, a, k, ltemp, rtemp)) {
                vmax = mid;
                L = ltemp; R = rtemp;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        cout << vmax << " " << L << " " << R << "\n";
    }

    return 0;   
}
