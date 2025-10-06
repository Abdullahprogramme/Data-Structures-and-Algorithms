#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Statement {
    char type;
    int pos;
};

int main() {
    int N;
    scanf("%d", &N);

    vector<Statement> statements(N);
    vector<int> positions;

    for (int i = 0; i < N; ++i) {
        char t;
        int p;
        scanf(" %c %d", &t, &p);
        statements[i] = {t, p};
        positions.push_back(p);
    }

    // Try all possible positions (including one beyond each pi)
    int min_liars = N;
    for (int i = 0; i < N; ++i) {
        for (int delta = -1; delta <= 1; ++delta) {
            int x = positions[i] + delta;
            int liars = 0;
            for (int j = 0; j < N; ++j) {
                if (statements[j].type == 'L') {
                    if (x > statements[j].pos) liars++;
                } else {
                    if (x < statements[j].pos) liars++;
                }
            }
            min_liars = min(min_liars, liars);
        }
    }

    printf("%d\n", min_liars);
    return 0;
}