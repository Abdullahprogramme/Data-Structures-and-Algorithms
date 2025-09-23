#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("lostcow.in", "r", stdin);
    freopen("lostcow.out", "w", stdout);

    int x, y;
    scanf("%d %d", &x, &y);

    int dir = 1;
    int step = 1;
    int pos = x;
    int total = 0;

    while (true) {
        int next = x + dir * step;
        // Check if Bessie is between pos and next (inclusive)
        if ((pos <= y && y <= next) || (pos >= y && y >= next)) {
            total += abs(y - pos);
            break;
        } else {
            total += abs(next - pos);
        }
        pos = next;
        dir *= -1;
        step *= 2;
    }

    printf("%d\n", total);
    return 0;
}