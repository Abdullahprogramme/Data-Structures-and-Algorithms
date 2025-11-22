#include "./Outcast.hpp"

#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

Outcast::Outcast(const WordNet& wn) : wnRef(wn) {}

string Outcast::outcast(const vector<string>& nouns) const {
    if (nouns.size() < 2) throw std::invalid_argument("outcast requires at least two nouns");

    long long bestSum = numeric_limits<long long>::min();
    string bestNoun;

    for (size_t i = 0; i < nouns.size(); ++i) {
        const string& xi = nouns[i];
        long long sum = 0;

        for (size_t j = 0; j < nouns.size(); ++j) {
            if (i == j) continue; // ignore self-distance

            const string& xj = nouns[j];
            sum += wnRef.distance(xi, xj);
        }

        if (sum > bestSum) { 
            bestSum = sum; 
            bestNoun = xi; 
        }
    }

    return bestNoun;
}