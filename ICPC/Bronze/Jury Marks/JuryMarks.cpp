#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;

    vector<long long> a(k);
    for (int i = 0; i < k; ++i)
        cin >> a[i];

    vector<long long> b(n);
    for (int i = 0; i < n; ++i)
        cin >> b[i];

    // Compute prefix sums
    vector<long long> prefix(k);
    prefix[0] = a[0];
    for (int i = 1; i < k; ++i)
        prefix[i] = prefix[i - 1] + a[i];

    unordered_set<long long> result;

    // Try each prefix as candidate base for b[0]
    for (int i = 0; i < k; ++i) {
        long long x = b[0] - prefix[i];

        // Build all possible announced scores for this x
        unordered_set<long long> announced;
        for (int j = 0; j < k; ++j)
            announced.insert(x + prefix[j]);

        // Check if all remembered b's fit
        bool valid = true;
        for (long long val : b)
            if (!announced.count(val)) {
                valid = false;
                break;
            }

        if (valid) result.insert(x);
    }

    cout << result.size() << "\n";
    return 0;
}
