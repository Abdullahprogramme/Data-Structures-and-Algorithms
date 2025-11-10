#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <string>

using namespace std;

/**
 * Return the minimum number of actions
 *
 * N: a non-negative integer representing the number of rows
 * M: another non-negative integer representing the number of columns
 * S: A string representing a sequence of drift inputs
 * G: N x M array representing a grid
 */

int char_drow(char c) {
    if (c == 'U') return -1;
    if (c == 'D') return 1;
    return 0;
}
int char_dcol(char c) {
    if (c == 'L') return -1;
    if (c == 'R') return 1;
    return 0;
}

tuple<int,int,int> bfs_to_target(int N, int M, const string &s, vector<vector<int>> &G,
                                int sr, int sc, int start_time, int target) {
    int L = (int)s.size();
    int total_states = N * M * L;
    vector<int> dist(total_states, -1);
    auto idx = [&](int r, int c, int tmod) { return (r * M + c) * L + tmod; };

    queue<tuple<int,int,int>> q;
    dist[idx(sr, sc, start_time)] = 0;
    q.emplace(sr, sc, start_time);

    // actions: do nothing, up, down, left, right
    const int ar[5] = {0, -1, 1, 0, 0};
    const int ac[5] = {0, 0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c, tmod] = q.front(); q.pop();
        int d = dist[idx(r,c,tmod)];
        if (G[r][c] == target) {
            return {d, r, c};
        }
        int next_t = (tmod + 1) % L;
        int drow = char_drow(s[tmod]);
        int dcol = char_dcol(s[tmod]);
        for (int a = 0; a < 5; ++a) {
            int nr = (r + ar[a] + drow) % N;
            if (nr < 0) nr += N;
            int nc = (c + ac[a] + dcol) % M;
            if (nc < 0) nc += M;
            int id = idx(nr, nc, next_t);
            if (dist[id] == -1) {
                dist[id] = d + 1;
                q.emplace(nr, nc, next_t);
            }
        }
    }
    return {-1, -1, -1};
}

int dfs(int N, int M, string s, vector<vector<int>> &G) { 
    int L = (int)s.size();
    int total_cells = N * M;
    int cur_r = 0, cur_c = 0, cur_tmod = 0;
    long long total_actions = 0;

    for (int target = 1; target <= total_cells; ++target) {
        if (G[cur_r][cur_c] == target) {
            // already on target, no action needed; time unchanged
            continue;
        }
        auto [steps, nr, nc] = bfs_to_target(N, M, s, G, cur_r, cur_c, cur_tmod, target);
        if (steps == -1) return -1;
        total_actions += steps;
        // update time mod after taking 'steps' actions
        cur_tmod = (cur_tmod + steps) % L;
        cur_r = nr;
        cur_c = nc;
    }
    return (int)total_actions;
}

int solve(int N, int M, string s, vector<vector<int>> &G) {
    vector<bool> vals(N * M + 1, false);
    return dfs(N, M, s, G);
}


int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M;
        cin >> N >> M;
        string S;
        cin >> S;
        vector<vector<int>> G(N, vector<int>(M));
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                cin >> G[j][k];
            }
        }
        cout << solve(N, M, S, G) << '\n';
    }
}