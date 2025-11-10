#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int checkDirection(const vector<vector<char>>& grid, int x, int y, int dx, int dy, int N, int M) {
	int row = x + dx;;
	int col = y + dy;

	while (row >= 0 && row < N && col >= 0 && col < M) {
		if (grid[row][col] != '.') {
			return 1;
		}

		row += dx;
		col += dy;
	}

	return 0;
}

int isHorizontal(const vector<vector<char>>& grid, int x, int y, int N, int M) {
	return checkDirection(grid, x, y, 0, 1, N, M) + checkDirection(grid, x, y, 0, -1, N, M);
}

int isVertical(const vector<vector<char>>& grid, int x, int y, int N, int M) {
	return checkDirection(grid, x, y, 1, 0, N, M) + checkDirection(grid, x, y, -1, 0, N, M);
}

int isDiagonal(const vector<vector<char>>& grid, int x, int y, int N, int M) {
	return checkDirection(grid, x, y, 1, 1, N, M) + checkDirection(grid, x, y, 1, -1, N, M) +
	       checkDirection(grid, x, y, -1, 1, N, M) + checkDirection(grid, x, y, -1, -1, N, M);
}

int solve(int N, int M, int K, vector<tuple<char, int, int>> P) {
    // N: Number of rows of the board
    // M: Number of columns of the board
    // K: Number of pieces
    // P: list of tuples. Each tuple contains (piece type, x position, y position)

    // YOUR CODE HERE
    vector<vector<char>> grid(N, vector<char>(M, '.'));
	for (auto [type, x, y] : P) {
		grid[x - 1][y - 1] = type;
	}

	int count = 0;

	for (auto [type, x, y] : P) {
		x -= 1; y -= 1;
		if (type == 'R') {
			count += isHorizontal(grid, x, y, N, M);
			count += isVertical(grid, x, y, N, M);
		} else if (type == 'B') {
			count += isDiagonal(grid, x, y, N, M);
		} else if (type == 'Q') {
			count += isHorizontal(grid, x, y, N, M);
			count += isVertical(grid, x, y, N, M);
			count += isDiagonal(grid, x, y, N, M);
		}
	}

	return count;
}

int main() {
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		int n, m; cin >> n >> m;
		int k, K; cin >> k;
		K = k;
		vector<tuple<char, int, int>> pieces;
		while (k--) {
			char piece; int x, y; cin >> piece >> x >> y;
            pieces.emplace_back(piece, x, y);
		}
	    cout << solve(n, m, K, pieces) << "\n";
	}
}
