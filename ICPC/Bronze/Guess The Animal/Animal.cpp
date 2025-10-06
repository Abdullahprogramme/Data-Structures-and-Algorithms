#include <stdio.h>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main() {
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);

    int N;
    scanf("%d", &N);

    vector<set<string>> animals(N);
    for (int i = 0; i < N; i++) {
        char name[21];
        int K;
        scanf("%s %d", name, &K);
        for (int j = 0; j < K; j++) {
            char trait[21];
            scanf("%s", trait);
            animals[i].insert(trait);
        }
    }

    int max_common = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int common = 0;
            for (const string& trait : animals[i]) {
                if (animals[j].count(trait)) common++;
            }
            if (common > max_common) max_common = common;
        }
    }

    printf("%d\n", max_common + 1);
    return 0;
}