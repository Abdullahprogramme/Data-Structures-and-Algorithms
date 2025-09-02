#include <vector>
#include <iostream>
#include <fstream>
#include "stopwatch.hpp"

using namespace std;

int count(const vector<int>& a) {
    int n = a.size();

    int c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                if (a[i] + a[j] + a[k] == 0) {
                    c++;
                }
            }
        }
    }

    return c;
}

int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    vector<int> a; int x;
    while (in >> x) {
        a.push_back(x);
    }

    Stopwatch sw;
    int result = count(a);
    double elapsed = sw.elapsedTime();
    cout << "Count: " << result << endl;
    cout << "Elapsed time: " << elapsed << " seconds" << endl;
}

