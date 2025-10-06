#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    int N, B;
    scanf("%d %d", &N, &B);

    vector<pair<int, int>> cows(N);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        cows[i] = make_pair(x, y);
    }

    int M = 0; // Maximum number of cows in any quadrant, to be minimized

    // Iterate over all pairs of cows to determine potential fence positions
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int fenceX = cows[i].first + 1;
            int fenceY = cows[j].second + 1;

            int Q1 = 0, Q2 = 0, Q3 = 0, Q4 = 0;

            // Count cows in each quadrant
            for (const auto& cow : cows) {
                if (cow.first > fenceX && cow.second > fenceY) {
                    Q1++;
                } else if (cow.first < fenceX && cow.second > fenceY) {
                    Q2++;
                } else if (cow.first < fenceX && cow.second < fenceY) {
                    Q3++;
                } else if (cow.first > fenceX && cow.second < fenceY) {
                    Q4++;
                }
            }

            int currentMax = max({Q1, Q2, Q3, Q4});
            M = (M == 0) ? currentMax : min(M, currentMax);
        }
    }

    printf("%d\n", M);

    return 0;
}