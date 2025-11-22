#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class WordNet {
    private:
        struct wordnet;
        wordnet* p_wordnet;

    public:
        // Constructor takes two input file names (synsets and hypernyms)
        WordNet(const string& synsetsFile, const string& hypernymsFile);

        // destructor
        ~WordNet();

        // returns all WordNet nouns
        const unordered_set<string>& nouns() const;

        // is the word a WordNet noun?
        bool isNoun(const string& word) const;

        // a synset (i.e., the synonym set) that is a shortest common ancestor of noun1 and noun2
        string sca(const string& noun1, const string& noun2) const;

        // distance between noun1 and noun2
        int distance(const string& noun1, const string& noun2) const;
};