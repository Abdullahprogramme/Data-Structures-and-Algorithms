#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("kayaking.in", "r", stdin);
    freopen("kayaking.out", "w", stdout);
    
    int n;
    scanf("%d", &n);
    vector<int> weights(2*n);
    for (int i = 0; i < 2*n; ++i) {
        scanf("%d", &weights[i]);
    }

    sort(weights.begin(), weights.end());

    int total_instability = 0;
    for (int i = 0; i < 2*(n - 1); i += 2) {
        total_instability += weights[i+1] - weights[i];
    }

    printf("%d\n", total_instability);

    return 0;
}