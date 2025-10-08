#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // weight for position k is number of subarrays that include k: (k+1)*(n-k)
    vector<long long> x(n);
    for (int k = 0; k < n; ++k) {
        long long w = 1LL * (k + 1) * (n - k);
        x[k] = w * a[k];
    }

    // To minimize sum x_i * y_perm(i), sort x ascending and b descending
    sort(x.begin(), x.end());
    sort(b.begin(), b.end(), greater<long long>());

    long long ans = 0;
    for (int i = 0; i < n; ++i) ans += x[i] * b[i];

    cout << ans << '\n';
    return 0;
}
