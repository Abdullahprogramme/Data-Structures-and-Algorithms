#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Segment {
    string type;
    int a, b; // range [a, b]
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);

    int N;
    cin >> N;
    vector<Segment> segs(N);

    for (int i = 0; i < N; i++) {
        cin >> segs[i].type >> segs[i].a >> segs[i].b;
    }

    // ---------- Backward pass ----------
    int low = 0, high = 1000; // start with [0, ∞], but cap at 1000 since inputs are bounded
    for (int i = N - 1; i >= 0; i--) {
        if (segs[i].type == "on") {
            // before this, flow was smaller
            low = max(0, low - segs[i].b);
            high = max(0, high - segs[i].a);
        } else if (segs[i].type == "off") {
            // before this, flow was larger
            low = low + segs[i].a;
            high = high + segs[i].b;
        } else { // "none"
            low = max(low, segs[i].a);
            high = min(high, segs[i].b);
        }
    }
    cout << low << " " << high << "\n";

    // ---------- Forward pass ----------
    for (int i = 0; i < N; i++) {
        if (segs[i].type == "on") {
            low = low + segs[i].a;
            high = high + segs[i].b;
        } else if (segs[i].type == "off") {
            low = max(0, low - segs[i].b);
            high = max(0, high - segs[i].a);
        } else { // "none"
            low = max(low, segs[i].a);
            high = min(high, segs[i].b);
        }
    }
    cout << low << " " << high << "\n";

    return 0;
}
