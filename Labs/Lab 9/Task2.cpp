#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <functional>
#include <algorithm>

using namespace std;

struct Cell {
    bool north;
    bool east;
    bool south;
    bool west;
};

int main() {
    ifstream infile("maze.txt");
    if (!infile) {
        cerr << "Error opening maze.txt\n";
        return 1;
    }

    int rows, cols;
    if (!(infile >> rows >> cols)) {
        cerr << "Invalid maze.txt header\n";
        return 1;
    }

    vector<vector<Cell>> grid(rows, vector<Cell>(cols));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int n, e, s, w;
            if (!(infile >> n >> e >> s >> w)) {
                cerr << "Unexpected EOF or malformed maze.txt at cell " << r << "," << c << "\n";
                return 1;
            }
            grid[r][c].north = (n == 1);
            grid[r][c].east  = (e == 1);
            grid[r][c].south = (s == 1);
            grid[r][c].west  = (w == 1);
        }
    }

    infile.close();

    // Maze uses padding: real cells are 1..rows-2 and 1..cols-2
    int startx = 1, starty = 1;
    int goalx = cols - 2, goaly = rows - 2;

    // visited and parent arrays
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int,int>>> parent(rows, vector<pair<int,int>>(cols, {-1,-1}));

    // DFS to find path
    function<bool(int,int)> explore = [&](int x, int y) -> bool {
        visited[y][x] = true;
        if (x == goalx && y == goaly) return true;

        // north: (x, y+1)
        if (!grid[y][x].north) {
            int nx = x, ny = y + 1;
            if (!visited[ny][nx]) {
                parent[ny][nx] = {x,y};
                if (explore(nx, ny)) return true;
            }
        }

        // east: (x+1, y)
        if (!grid[y][x].east) {
            int nx = x + 1, ny = y;
            if (!visited[ny][nx]) {
                parent[ny][nx] = {x,y};
                if (explore(nx, ny)) return true;
            }
        }

        // south: (x, y-1)
        if (!grid[y][x].south) {
            int nx = x, ny = y - 1;
            if (!visited[ny][nx]) {
                parent[ny][nx] = {x,y};
                if (explore(nx, ny)) return true;
            }
        }

        // west: (x-1, y)
        if (!grid[y][x].west) {
            int nx = x - 1, ny = y;
            if (!visited[ny][nx]) {
                parent[ny][nx] = {x,y};
                if (explore(nx, ny)) return true;
            }
        }

        return false;
    };

    bool found = explore(startx, starty);
    if (!found) {
        cout << "No path found from (1,1) to (" << goalx << "," << goaly << ")\n";
        return 0;
    }

    // reconstruct path from goal to start
    vector<pair<int,int>> path;
    int cx = goalx, cy = goaly;
    while (!(cx == -1 && cy == -1)) {
        path.push_back({cx, cy});
        auto p = parent[cy][cx];
        cx = p.first; cy = p.second;
        if (cx == startx && cy == starty) { 
            path.push_back({startx, starty}); 
            break; 
        }
    }
    reverse(path.begin(), path.end());

    
    cout << "Path length: " << path.size() << "\n";
    for (auto &pt : path) {
        cout << "(" << pt.first << "," << pt.second << ")\n";
    }

    int n = rows - 2;
    vector<vector<char>> cellmark(rows, vector<char>(cols, ' '));
    for (auto &p : path) cellmark[p.second][p.first] = '.';

    cout << "Maze:\n";
    for (int y = rows - 2; y >= 1; --y) {
        // top
        for (int x = 1; x <= cols - 2; ++x) {
            cout << '+';
            cout << (grid[y][x].north ? "---" : "   ");
        }
        cout << "+\n";

        // middle
        for (int x = 1; x <= cols - 2; ++x) {
            cout << (grid[y][x].west ? "|" : " ");
            cout << " ";
            cout << (cellmark[y][x] == '.' ? '.' : ' ');
            cout << " ";
        }
        cout << (grid[y][cols-2].east ? "|\n" : " \n");
    }

    // bottom
    for (int x = 1; x <= cols - 2; ++x) {
        cout << '+';
        cout << (grid[1][x].south ? "---" : "   ");
    }
    cout << "+\n";

    return 0;
}