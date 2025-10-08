#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    int N;
    scanf("%d", &N);

    vector<int> positions(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &positions[i]);
    }

    sort(positions.begin(), positions.end());

    int max_count = 0;
    for (int start = 0; start < N; start++) {
        vector<bool> exploded(N, false);
        queue<pair<int, int>> q; // {index, current_radius}
        exploded[start] = true;
        q.push({start, 1});
        int count = 1;

        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int idx = q.front().first;
                int radius = q.front().second;
                q.pop();

                // Check to the right
                for (int j = idx + 1; j < N; j++) {
                    if (!exploded[j] && positions[j] - positions[idx] <= radius) {
                        exploded[j] = true;
                        q.push({j, radius + 1});
                        count++;
                    } else if (positions[j] - positions[idx] > radius) {
                        break;
                    }
                }
                
                // Check to the left
                for (int j = idx - 1; j >= 0; j--) {
                    if (!exploded[j] && positions[idx] - positions[j] <= radius) {
                        exploded[j] = true;
                        q.push({j, radius + 1});
                        count++;
                    } else if (positions[idx] - positions[j] > radius) {
                        break;
                    }
                }
            }
        }

        max_count = max(max_count, count);
    }

    printf("%d\n", max_count);

    return 0;
}