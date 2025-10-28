#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <sstream>

// including hash table and stopwatch
#include "hashTable.hpp"
#include "stopWatch.hpp"

using namespace std;

vector<vector<char>> readInGrid(const string &filename) {
    ifstream fin(filename.c_str());
    if (!fin.is_open()) return vector<vector<char>>();

    int rows, cols;
    fin >> rows >> cols;
    vector<vector<char>> grid(rows, vector<char>(cols));

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            fin >> grid[r][c];
        }
    }

    fin.close();

    return grid;
}

string getWordInGrid(const vector<vector<char>>& grid, int startRow, int startCol, int dir, int len) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    string output;
    int r = startRow, c = startCol;

    for (int i = 0; i < len; i++) {
        if (r < 0 || r >= numRows || c < 0 || c >= numCols) break;
        
        output.push_back(grid[r][c]);
        switch(dir){
            case 0: r--; break; // N
            case 1: r--; c++; break; // NE
            case 2: c++; break; // E
            case 3: r++; c++; break; // SE
            case 4: r++; break; // S
            case 5: r++; c--; break; // SW
            case 6: c--; break; // W
            case 7: r--; c--; break; // NW
        }
    }

    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <dictionary_file> <grid_file>" << endl;
        return 1;
    }

    string dictFile = argv[1];
    string gridFile = argv[2];

    // Read dictionary (two simple passes: load into vector to size table appropriately)
    ifstream din(dictFile.c_str());
    if (!din.is_open()) { 
        cout << "Error opening dictionary file" << endl; return 1; 
    }

    vector<string> words;
    size_t maxWordLen = 0;
    string line;

    while (getline(din, line)){
        // trim whitespace
        string w;
        for (char ch : line) {
            if (!isspace((unsigned char)ch)) w.push_back(ch);
        }

        if (w.size() < 3) continue; // ignore short words

        bool ok = true;
        for (char ch : w) if (!isalpha((unsigned char)ch)) { 
            ok = false; 
            break; 
        }

        if (!ok) continue;
        words.push_back(w);

        if (w.size() > maxWordLen) maxWordLen = w.size();
    }

    din.close();

    // Build hash table
    HashTable ht(words.size() * 2 + 3);
    ht.setMaxWordLength(maxWordLen);
    for (const auto &w : words) {
        ht.insertWord(w);
        // insert prefixes of length >=3
        for (size_t L = 3; L + 1 <= w.size(); ++L) {
            string pref = w.substr(0, L);
            ht.insertPrefix(pref);
        }
    }

    // Read grid
    vector<vector<char>> grid = readInGrid(gridFile);
    if (grid.size() == 0) { 
        cout << "Error reading grid file" << endl; 
        return 1; 
    }

    const char *dirNames[8] = {"N","NE","E","SE","S","SW","W","NW"};
    vector<pair<string,string>> occurrences; // pair<header, word>
    vector<string> foundWords;

    Stopwatch sw; // timer starts now
    sw.reset();

    int rows = grid.size();
    int cols = grid[0].size();
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            for (int d = 0; d < 8; d++) {
                for (size_t L = 3; L <= maxWordLen; L++) {
                    string s = getWordInGrid(grid, r, c, d, (int)L);
                    
                    if (s.size() < L) break; // went off edge
                    if (!ht.containsPrefix(s)) break; // no words with this prefix
                    if (ht.containsWord(s)) {
                        ostringstream hdr;
                        hdr << dirNames[d] << " (" << r << ", " << c << "):";
                        occurrences.emplace_back(hdr.str(), s);
                        foundWords.push_back(s);
                    }
                }
            }
        }
    }

    double elapsed = sw.elapsedTime();

    // Print occurrences in required-ish format
    for (auto &p : occurrences) {
        cout << p.first << " " << left << setw(20) << p.second << right << endl;
    }

    cout << foundWords.size() << " words found" << endl;

    cout << "Found all words in " << fixed << setprecision(6) << elapsed << " seconds" << endl;

    return 0;
}

