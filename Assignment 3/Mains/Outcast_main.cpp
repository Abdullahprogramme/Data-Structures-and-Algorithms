#include "./WordNet.hpp"
#include "./Outcast.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    try {
        int K = 20; // default sample size
        if (argc >= 2) {
            try { 
                K = max(2, stoi(argv[1])); 
            } catch(...) {}
        }

        WordNet wn("synsets.csv", "hypernyms.csv");
        Outcast oc(wn);

        if (K > wn.nouns().size()) {
            K = (int)wn.nouns().size();
        }

        // collect first K nouns
        vector<string> alln(wn.nouns().begin(), wn.nouns().end());
        if ((int)alln.size() <= K) {
            K = (int)alln.size();
        }

        vector<string> nouns(alln.begin(), alln.begin() + K);

        cout << "Running Outcast over " << nouns.size() << " nouns (first " << K << ")\n";
        string out = oc.outcast(nouns);

        cout << "Outcast result: " << out << '\n';
        return 0;

    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << '\n';
        return 3;
    }
}
