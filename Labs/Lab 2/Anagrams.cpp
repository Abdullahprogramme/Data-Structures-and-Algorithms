#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

// part (a) generating a list of n = 1000 words
string random_word(int m) {
    string s;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 25);

    for (int i = 0; i < m; ++i) {
        s.push_back('a' + dis(gen));
    }

    return s;
}

void generateList(vector<string>& words, int n = 1000, int m = 10) {
    // Ensure the list contains anagrams: generate n/2 pairs
    for (int i = 0; i < n / 2; ++i) {
        string s = random_word(m);
        words.push_back(s);
        string t = s;
        shuffle(t.begin(), t.end(), default_random_engine(random_device()()));
        words.push_back(t);
    }
}

// part (b) O(n^2) algo to find all anagrams of the words
// O(n^2) algorithm to find all anagram pairs
void findAnagrams_n2(const vector<string>& words) {
    cout << "O(n^2) anagram pairs:" << endl;
    int n = words.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            string a = words[i], b = words[j];
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());
            if (a == b) {
                cout << words[i] << " <-> " << words[j] << endl;
            }
        }
    }
}
// part (c) O(nlogn) algo to find all anagrams of the words
// O(n log n) algorithm to group anagrams
void findAnagrams_nlogn(vector<string> words) {
    cout << "O(n log n) anagram groups:" << endl;
    int n = words.size();
    vector<pair<string, string>> sorted_words;

    for (const auto& w : words) {
        string sorted_w = w;
        sort(sorted_w.begin(), sorted_w.end());
        sorted_words.emplace_back(sorted_w, w);
    }
    sort(sorted_words.begin(), sorted_words.end());
    
    for (int i = 0; i < n;) {
        int j = i + 1;
        while (j < n && sorted_words[i].first == sorted_words[j].first) ++j;
        if (j - i > 1) {
            cout << "Group: ";
            for (int k = i; k < j; ++k) cout << sorted_words[k].second << " ";
            cout << endl;
        }
        i = j;
    }
}

int main() {
    vector<string> words;
    generateList(words, 1000, 10);
    findAnagrams_n2(words);
    findAnagrams_nlogn(words);
    return 0;
}