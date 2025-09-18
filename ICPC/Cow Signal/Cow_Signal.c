#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("cowsignal.in", "r", stdin);
    freopen("cowsignal.out", "w", stdout);

    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);

    char grid[15][15]; 
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }

    for (int i = 0; i < m; i++) {
        for (int ki = 0; ki < k; ki++) { // vertical scaling
            for (int j = 0; j < n; j++) {
                for (int kj = 0; kj < k; kj++) { // horizontal scaling
                    putchar(grid[i][j]);
                }
            }
            putchar('\n');
        }
    }

    return 0;
}