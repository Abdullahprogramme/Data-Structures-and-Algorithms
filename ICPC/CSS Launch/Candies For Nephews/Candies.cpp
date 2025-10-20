#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Candies.in", "r", stdin);
    freopen("Candies.out", "w", stdout);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int extras = 0;
        while (true) {
            if (n % 3 == 0) { 
                printf("%d\n", extras);
                break;
            } else {
                n++;
                extras++;
            }
        }
    }

    return 0;
}
