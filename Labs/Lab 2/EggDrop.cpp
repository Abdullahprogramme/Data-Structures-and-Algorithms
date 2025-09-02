#include <random>
#include <iostream>

using namespace std;

class EggDrop {
    private:
        int m;

    public:
        explicit EggDrop(int n) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(1, n);
            m = dist(gen);
        }

        bool operator()(int x) const {
            return x >= m;
        }
};

int main() {
    int n = 10000;
    EggDrop eggdrop(n);

    // Step 1: Probe powers of 2
    int k = 0;
    int probe = 1;
    while (probe < n && !eggdrop(probe)) {
        k++;
        probe = 1 << k; // 2^k
    }
    int lo = probe >> 1; // 2^{k-1}
    int hi = min(probe, n); // 2^k or n
    
    // Step 2: Binary search between lo and hi
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (eggdrop(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << "The value of m is " << lo << endl;
    return 0;
}