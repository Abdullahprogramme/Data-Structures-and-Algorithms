#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void solve(int N, int K, vector<int>& H, vector<int>& L) {
    // int sausages = H.size();
    // int high = *max_element(H.begin(), H.end());
    // int low = *min_element(L.begin(), L.end());
    

    // for (int i = high; i >= low; i--) {
    //     for (int j = i - 1; j > low; j--) {
    //         int total_sausages = 0;
    //         // iterating in the sausages vectors
    //         for (int s = 0; s < sausages; s++) {
    //             total_sausages += max(0, min(H[s], i) - max(L[s], j));
    //         }

    //         if (total_sausages == K) {
    //             cout << j << " " << i << endl;
    //             return;
    //         }
    //     }   
    // }

    // cout << "IMPOSSIBLE" << endl;

    vector<int> coords;
    for (int i = 0; i < N; i++) {
        coords.push_back(L[i]);
        coords.push_back(H[i]);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    int M = coords.size();

    vector<long long> diff(M + 1, 0);

    // Build difference array
    for (int i = 0; i < N; i++) {
        int l = lower_bound(coords.begin(), coords.end(), L[i]) - coords.begin();
        int h = lower_bound(coords.begin(), coords.end(), H[i]) - coords.begin();
        diff[l] += 1;
        diff[h] -= 1;
    }

    // Prefix sum for active sausage count
    vector<long long> active(M, 0);
    active[0] = diff[0];
    for (int i = 1; i < M; i++) active[i] = active[i - 1] + diff[i];

    // Cumulative sausage count along height
    vector<long long> prefix(M, 0);
    for (int i = 1; i < M; i++) {
        long long height_diff = coords[i] - coords[i - 1];
        prefix[i] = prefix[i - 1] + active[i - 1] * height_diff;
    }

    // Two-pointer search
    int j = 0;
    for (int i = 0; i < M; i++) {
        while (j < M && prefix[j] - prefix[i] < K) j++;
        if (j < M && prefix[j] - prefix[i] == K) {
            cout << coords[i] << " " << coords[j] << "\n";
            return;
        }
    }

    cout << "IMPOSSIBLE\n";
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
