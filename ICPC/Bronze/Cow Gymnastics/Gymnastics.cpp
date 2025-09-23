#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);

    int K, N;
    scanf("%d %d", &K, &N);

    vector<vector<int>> rankings(K, vector<int>(N));
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &rankings[i][j]);
            rankings[i][j]--; // Convert to 0-based index
        }
    }

    int consistentPairs = 0;
    for (int a = 0; a < N; a++) {
        for (int b = a + 1; b < N; b++) {
            if (a == b) continue;

            bool isConsistent = true;
            bool aBetterThanB = false;

            for (int k = 0; k < K; k++) {
                int posA = find(rankings[k].begin(), rankings[k].end(), a) - rankings[k].begin();
                int posB = find(rankings[k].begin(), rankings[k].end(), b) - rankings[k].begin();

                if (posA < posB) {
                    if (!aBetterThanB && k > 0) {
                        isConsistent = false;
                        break;
                    }
                    aBetterThanB = true;
                } else {
                    if (aBetterThanB && k > 0) {
                        isConsistent = false;
                        break;
                    }
                    aBetterThanB = false;
                }
            }

            if (isConsistent) {
                consistentPairs++;
            }
        }
    }

    printf("%d\n", consistentPairs);
    return 0;
}