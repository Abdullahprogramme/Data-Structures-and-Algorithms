#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <fstream>

using namespace std;

struct Cell {
    bool north = true;
    bool east = true;
    bool south = true;
    bool west = true;
    bool visited = false;
};

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " n\n";
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        cerr << "n must be > 0\n";
        return 1;
    }

    // a (n + 2) x (n + 2) grid
    vector<vector<Cell>> grid(n+2, vector<Cell>(n+2));
    // mark border cells as visited so algorithm won't try to step outside
    for (int i = 0; i <= n + 1; i++) { 
        grid[0][i].visited = grid[n + 1][i].visited = true; 
        grid[i][0].visited = grid[i][n + 1].visited = true; 
    }

    // random
    random_device rd;
    mt19937 rng(rd());

    // iterative DFS (stack)
    vector<pair<int,int>> st;
    int cx = 1, cy = 1;
    grid[cy][cx].visited = true;
    st.push_back({cx, cy});

    auto neighbors = [&](int x, int y) {
        vector<pair<int,int>> nb;

        if (!grid[y + 1][x].visited) nb.push_back({x, y + 1}); // north
        if (!grid[y][x + 1].visited) nb.push_back({x + 1, y}); // east
        if (!grid[y - 1][x].visited) nb.push_back({x, y - 1}); // south
        if (!grid[y][x - 1].visited) nb.push_back({x - 1, y}); // west

        return nb;
    };

    while (!st.empty()) {
        tie(cx,cy) = st.back();
        auto nb = neighbors(cx, cy);
        if (!nb.empty()) {
            uniform_int_distribution<int> dist(0, (int)nb.size()-1);
            auto [nx, ny] = nb[dist(rng)];
            
            // knock down wall between (cx,cy) and (nx,ny)
            if (nx == cx && ny == cy + 1) { 
                grid[cy][cx].north = false; 
                grid[ny][nx].south = false; 
            } else if (nx == cx + 1 && ny == cy) { 
                grid[cy][cx].east = false; 
                grid[ny][nx].west = false; 
            } else if (nx == cx && ny == cy - 1) { 
                grid[cy][cx].south = false; 
                grid[ny][nx].north = false; 
            } else if (nx == cx - 1 && ny == cy) { 
                grid[cy][cx].west = false; 
                grid[ny][nx].east = false; 
            }
            // move
            grid[ny][nx].visited = true;
            st.push_back({nx, ny});
        } else {
            st.pop_back();
        }
    }

    ofstream outfile("maze.txt");
    outfile << n + 2 << " " << n + 2 << "\n";
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            outfile << (grid[i][j].north ? 1 : 0) << " "
                    << (grid[i][j].east ? 1 : 0) << " "
                    << (grid[i][j].south ? 1 : 0) << " "
                    << (grid[i][j].west ? 1 : 0) << "\n";
        }
    }

    for (int y = n; y >= 1; --y) {
        // top line
        for (int x = 1; x <= n; ++x) {
            cout << '+';
            cout << (grid[y][x].north ? "---" : "   ");
        }
        cout << "+\n";

        // middle line 
        for (int x = 1; x <= n; ++x) {
            cout << (grid[y][x].west ? "|" : " ");
            cout << "   ";
        }
        cout << (grid[y][n].east ? "|\n" : " \n");
    }
    
    // bottom line
    for (int x = 1; x <= n; ++x) {
        cout << '+';
        cout << (grid[1][x].south ? "---" : "   ");
    }
    cout << "+\n";

    return 0;
}