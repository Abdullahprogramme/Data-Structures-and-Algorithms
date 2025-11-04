#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>

using namespace std;

int main() {
    ifstream infile("supportfiles/words.txt");
    if (!infile) {
        cerr << "Error opening supportfiles/words.txt\n";
        return 1;
    }

    unordered_set<string> dict;
    string w;
    size_t maxLen = 0;
    while (infile >> w) {
        dict.insert(w);
        if (w.size() > maxLen) maxLen = w.size();
    }
    infile.close();

    // Group words by length
    vector<vector<string>> byLen(maxLen + 1);
    for (auto &word : dict) {
        byLen[word.size()].push_back(word);
    }

    // Build directed edges from longer -> shorter by removing one letter
    unordered_map<string, vector<string>> edges;
    for (size_t len = 2; len <= maxLen; ++len) {
        for (auto &longer : byLen[len]) {
            string candidate;
            candidate.reserve(len - 1);
            for (size_t i = 0; i < len; ++i) {
                candidate.clear();

                // removing the i-th character
                candidate.append(longer.begin(), longer.begin() + i);
                candidate.append(longer.begin() + i + 1, longer.end());
                if (dict.find(candidate) != dict.end()) {
                    edges[longer].push_back(candidate);
                }
            }
        }
    }

    // DFS
    unordered_map<string, vector<string>> bestChains;
    function<vector<string>(const string&)> longestChain = [&](const string &node) -> vector<string> {
        auto it = bestChains.find(node);
        if (it != bestChains.end()) return it->second;

        vector<string> best;
        auto eit = edges.find(node);

        if (eit != edges.end()) {
            for (auto &nbr : eit->second) {
                vector<string> chain = longestChain(nbr);
                if (chain.size() > best.size()) best = move(chain);
            }
        }
        
        // prepend current node
        vector<string> result;
        result.reserve(1 + best.size());
        result.push_back(node);
        result.insert(result.end(), best.begin(), best.end());
        bestChains[node] = result;
        return result;
    };

    // Try all 9-letter words
    size_t targetLen = 9;
    if (targetLen > maxLen) {
        cerr << "No words of length " << targetLen << " in dictionary.\n";
        return 1;
    }

    for (auto &start : byLen[targetLen]) {
        vector<string> chain = longestChain(start);
        
        if (chain.size() == targetLen) {
            // verify final word length is 1
            if (!chain.empty() && chain.back().size() == 1) {
                // print chain
                for (size_t i = 0; i < chain.size(); ++i) {
                    if (i) cout << " -> ";
                    cout << chain[i];
                }
                cout << "\n";
                return 0;
            }
        }
    }

    cout << "No nine-letter reducible word found.\n";
    return 0;
}