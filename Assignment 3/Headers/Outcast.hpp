#pragma once

#include "WordNet.hpp"
#include <string>
#include <vector>

using namespace std;

class Outcast {
    private:
        const WordNet& wnRef;

    public:
        // Constructor takes a WordNet object
        Outcast(const WordNet& wn);

        // given a vector of WordNet nouns, return the outcast (least related noun)
        string outcast(const vector<string>& nouns) const;
};