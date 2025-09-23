#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    freopen("tttt.in", "r", stdin);
    freopen("tttt.out", "w", stdout);

    vector<vector<char>> board(3, vector<char>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> board[i][j];
        }
    }

    // Store winners
    set<char> single_winners;
    set<pair<char, char>> team_winners;

    // Collect all 8 lines
    vector<vector<char>> lines;

    // Rows
    for (int i = 0; i < 3; i++)
        lines.push_back({board[i][0], board[i][1], board[i][2]});
    // Cols
    for (int j = 0; j < 3; j++)
        lines.push_back({board[0][j], board[1][j], board[2][j]});
    // Diagonals
    lines.push_back({board[0][0], board[1][1], board[2][2]});
    lines.push_back({board[0][2], board[1][1], board[2][0]});

    // delete grid vector to save memory
    board.clear();
    board.shrink_to_fit();
    
    // Analyze each line
    for (auto &line : lines) {
        set<char> s(line.begin(), line.end());
        if (s.size() == 1) {
            // Single cow win
            single_winners.insert(*s.begin());
        } else if (s.size() == 2) {
            // Team win
            auto it = s.begin();
            char a = *it++;
            char b = *it;
            if (a > b) swap(a, b); // ensure consistent order
            team_winners.insert({a, b});
        }
    }

    cout << single_winners.size() << "\n" << team_winners.size() << "\n";
    return 0;
}
