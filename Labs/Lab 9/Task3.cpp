#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " startWord endWord\n";
        return 1;
    }

    string start = argv[1];
    string target = argv[2];

    auto confirmer = [](string &s){
        if (s.size() != 5) return false;
        for (auto &c : s) c = tolower((unsigned char)c);
        return true;
    };

    if (!confirmer(start) || !confirmer(target)) {
        cerr << "Both words must be 5 letters.\n";
        return 1;
    }

    ifstream infile("supportfiles/words5.txt");
    if (!infile) {
        cerr << "Error opening supportfiles/words5.txt\n";
        return 1;
    }

    unordered_set<string> dict;
    string w;
    while (infile >> w) {
        dict.insert(w);
    }
    infile.close();
    

    dict.insert(start);
    dict.insert(target);

    queue<string> q;
    unordered_map<string, string> parent;
    unordered_set<string> visited;

    q.push(start);
    visited.insert(start);

    bool found = false;
    while (!q.empty() && !found) {
        string cur = q.front(); q.pop();
        string next = cur;
        for (size_t i = 0; i < 5 && !found; ++i) {
            char orig = next[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == orig) continue;

                next[i] = c;
                if (dict.count(next) && !visited.count(next)) {
                    visited.insert(next);
                    parent[next] = cur;

                    if (next == target) { 
                        found = true; 
                        break; 
                    }

                    q.push(next);
                }
            }

            next[i] = orig;
        }
    }

    if (!found) {
        cout << "No word ladder found.\n";
        return 0;
    }

    // Reconstruct path
    vector<string> path;
    for (string cur = target; ; cur = parent[cur]) {
        path.push_back(cur);
        if (cur == start) break;
    }
    reverse(path.begin(), path.end());

    // Print ladder
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';

    return 0;
}