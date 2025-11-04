#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void solve(int N, int K, vector<int>& H, vector<int>& L) {
    int sausages = H.size();
    int high = *max_element(H.begin(), H.end());
    int low = *min_element(L.begin(), L.end());
    

    for (int i = high; i >= low; i--) {
        for (int j = i - 1; j > low; j--) {
            int total_sausages = 0;
            // iterating in the sausages vectors
            for (int s = 0; s < sausages; s++) {
                total_sausages += max(0, min(H[s], i) - max(L[s], j));
            }

            if (total_sausages == K) {
                cout << j << " " << i << endl;
                return;
            }
        }   
    }

    cout << "IMPOSSIBLE" << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N;
        int K;
        cin >> N >> K;
        vector<int> H(N);
        for (int j = 0; j < N; j++) {
            cin >> H[j];
        }
        vector<int> L(N);
        for (int j = 0; j < N; j++) {
            cin >> L[j];
        }

        solve(N, K, H, L);
    }
}
