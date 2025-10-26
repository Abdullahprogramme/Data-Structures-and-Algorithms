<<<<<<< HEAD
#include <iostream>
#include <vector>

using namespace std;

static const int MOD = 998244353;

long long modexp(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Grid.in", "r", stdin);
    freopen("Grid.out", "w", stdout);

    int T;
    cin >> T;

    int maxN = 200000;
    vector<long long> fact(maxN+1), invfact(maxN+1);
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++) fact[i] = fact[i-1] * i % MOD;
    invfact[maxN] = modexp(fact[maxN], MOD-2);
    for (int i = maxN; i > 0; i--) invfact[i-1] = invfact[i] * i % MOD;

    auto nCr = [&](int n, int r)->long long {
        if (r < 0 || r > n) return 0;
        return fact[n] * invfact[r] % MOD * invfact[n-r] % MOD;
    };

    while (T--){
        int n;
        cin >> n;
        vector<int> a(n+1);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }

        // From the editorial:
        // First check feasibility: For each i, a[i] ≤ available columns count for row i.
        long long ans = 1;
        int availableColumns = 0;

        // We'll process rows in decreasing order (i = n down to 1).
        // At step i, we compute how many new columns become "available" for row i.
        //
        // From the editorial: only cells (i, j) with i ≤ j AND i ≤ n−j+1 can be black.
        // So effectively for each column j, the unique black cell must satisfy i ≤ min(j, n−j+1).
        // So the total available columns for row i is: count of j such that min(j, n−j+1) ≥ i.
        // That count is: let k = i. Then j from k…(n−k+1). So count = (n−k+1) − k + 1 = n − 2k + 2.
        //
        // So we can maintain availableColumns = n−2*i+2, and subtract how many were used in previous rows.

        availableColumns = 0; // we will compute inside loop
        long long used = 0;   // how many black cells we have fixed in rows > i

        for (int i = n; i >= 1; i--){
            int c_i = n - 2*i + 2;  // number of columns j with min(j, n−j+1) ≥ i
            if (c_i < 0) c_i = 0;
            // subtract what has been used (in higher rows)
            int freeCols = c_i - used;
            if (freeCols < a[i]){
                ans = 0;
                break;
            }
            // choose a[i] columns out of freeCols
            ans = ans * nCr(freeCols, a[i]) % MOD;
            used += a[i];
        }

        cout << ans << "\n";
    }
    return 0;
}
=======
#include <iostream>
#include <vector>

using namespace std;

static const int MOD = 998244353;

long long modexp(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Grid.in", "r", stdin);
    freopen("Grid.out", "w", stdout);

    int T;
    cin >> T;

    int maxN = 200000;
    vector<long long> fact(maxN+1), invfact(maxN+1);
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++) fact[i] = fact[i-1] * i % MOD;
    invfact[maxN] = modexp(fact[maxN], MOD-2);
    for (int i = maxN; i > 0; i--) invfact[i-1] = invfact[i] * i % MOD;

    auto nCr = [&](int n, int r)->long long {
        if (r < 0 || r > n) return 0;
        return fact[n] * invfact[r] % MOD * invfact[n-r] % MOD;
    };

    while (T--){
        int n;
        cin >> n;
        vector<int> a(n+1);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }

        // From the editorial:
        // First check feasibility: For each i, a[i] ≤ available columns count for row i.
        long long ans = 1;
        int availableColumns = 0;

        // We'll process rows in decreasing order (i = n down to 1).
        // At step i, we compute how many new columns become "available" for row i.
        //
        // From the editorial: only cells (i, j) with i ≤ j AND i ≤ n−j+1 can be black.
        // So effectively for each column j, the unique black cell must satisfy i ≤ min(j, n−j+1).
        // So the total available columns for row i is: count of j such that min(j, n−j+1) ≥ i.
        // That count is: let k = i. Then j from k…(n−k+1). So count = (n−k+1) − k + 1 = n − 2k + 2.
        //
        // So we can maintain availableColumns = n−2*i+2, and subtract how many were used in previous rows.

        availableColumns = 0; // we will compute inside loop
        long long used = 0;   // how many black cells we have fixed in rows > i

        for (int i = n; i >= 1; i--){
            int c_i = n - 2*i + 2;  // number of columns j with min(j, n−j+1) ≥ i
            if (c_i < 0) c_i = 0;
            // subtract what has been used (in higher rows)
            int freeCols = c_i - used;
            if (freeCols < a[i]){
                ans = 0;
                break;
            }
            // choose a[i] columns out of freeCols
            ans = ans * nCr(freeCols, a[i]) % MOD;
            used += a[i];
        }

        cout << ans << "\n";
    }
    return 0;
}
>>>>>>> 856627f9fb38d9eb137e600c81d373364930179f
