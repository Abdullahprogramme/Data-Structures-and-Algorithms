#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    int n, k;
    scanf("%d %d", &n, &k);

    vector<int> diamonds(n);
    for (int i = 0; i < n; i++) {
        int d;
        scanf("%d", &d);
        diamonds[i] = d;
    }

    int max_val = 0;
    sort(diamonds.begin(), diamonds.end());

    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (diamonds[j] - diamonds[i] <= k) {
                count++;
            } else {
                break;
            }
        }
        max_val = max(max_val, count);
    }

    printf("%d\n", max_val);
    return 0;
}