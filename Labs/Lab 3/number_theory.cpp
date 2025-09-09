#include "maxpq_ra.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

struct ThreeTuple {
    int sum;
    int a;
    int b;

    // Comparison operator for min-heap using MaxPQ
    bool operator<(const ThreeTuple& other) const {
        return sum < other.sum;
    }
};

class NumberTheory {
    private:
        MaxPQ<ThreeTuple> pq; // min-heap, uses negative sum
        int N;

    public:
        NumberTheory(int n) : N(n) {
            for (int i = 0; i <= N; ++i) {
                pq.insert( {-(static_cast<int>(pow(i, 3)) + static_cast<int>(pow(i, 3))), i, i} ); // use negative for min-heap
            }
        }

        // Prints all a^3 + b^3 in sorted order
        void printSortedCubes() {
            while (!pq.empty()) {
                ThreeTuple t = pq.delMax();
                int sum = -t.sum; // revert sign

                cout << sum << " = " << t.a << "^3 + " << t.b << "^3\n";

                if (t.b < N) {
                    pq.insert( {-(static_cast<int>(pow(t.a, 3)) + static_cast<int>(pow(t.b + 1, 3))), t.a, t.b + 1} );
                }
            }
        }

        // Finds all distinct pairs (a,b), (c,d) such that a^3 + b^3 = c^3 + d^3
        void printHardyRamanujanNumbers() {
            unordered_map<int, vector<pair<int,int>>> sumMap;

            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= N; ++j) {
                    int sum = static_cast<int>(pow(i, 3)) + static_cast<int>(pow(j, 3));
                    sumMap[sum].emplace_back(i, j);
                }
            }

            for (const auto& entry : sumMap) {
                if (entry.second.size() > 1) {
                    cout << entry.first << ": ";

                    for (const auto& p : entry.second) {
                        cout << "(" << p.first << "," << p.second << ") ";
                    }

                    cout << "\n";
                }
            }
        }
};

int main() {
    int N = 12; // You can change this value for different ranges
    NumberTheory nt(N);

    cout << "Sorted sums of two cubes up to " << N << ":\n";
    nt.printSortedCubes();

    cout << "\nHardy-Ramanujan numbers up to " << N << ":\n";
    nt.printHardyRamanujanNumbers();

    return 0;
}