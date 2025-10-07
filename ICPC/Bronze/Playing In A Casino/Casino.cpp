#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("casino.in", "r", stdin);
    freopen("casino.out", "w", stdout);
    
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &grid[i][j]);
            }
        }

        int max_sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int current_sum = 0;
                for (int k = 0; k < m; ++k) {
                    current_sum += abs(grid[i][k] - grid[j][k]);
                }
                max_sum += current_sum;
            }
        }

        printf("%d\n", max_sum);
    }

    return 0;
}