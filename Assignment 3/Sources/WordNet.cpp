#include "./WordNet.hpp"
#include "./Digraph.hpp"
#include "./ShortestCommonAncestor.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

struct WordNet::wordnet {
    vector<string> idToSynset;
    unordered_map<string, vector<int>> nounToIds;
    unordered_set<string> nounSet;
    Digraph* G = nullptr;
    ShortestCommonAncestor* sca = nullptr;

    ~wordnet() { 
        delete G; 
        delete sca; 
    }
};

static void splitTwoCommas(const string& line, string& field1, string& field2) {
    // split into id, synset, gloss. We only need id and synset
    size_t p1 = line.find(',');
    if (p1 == string::npos) throw invalid_argument("bad synsets line");
    size_t p2 = line.find(',', p1 + 1);

    if (p2 == string::npos) {
        // allow missing gloss
        field1 = line.substr(0, p1);
        field2 = line.substr(p1 + 1);
    } else {
        field1 = line.substr(0, p1);
        field2 = line.substr(p1 + 1, p2 - (p1 + 1));
    }
}

WordNet::WordNet(const string& synsetsFile, const string& hypernymsFile) {
    if (synsetsFile.empty() || hypernymsFile.empty()) throw invalid_argument("empty filename");
    
    p_wordnet = new wordnet();
    ifstream fin(synsetsFile);
    if (!fin) { 
        delete p_wordnet
        ; throw invalid_argument("cannot open synsets file"); 
    }

    string line;
    int maxId = -1;

    // Read synsets
    while (getline(fin, line)) {
        if (line.empty()) continue;

        string idstr, synset;
        splitTwoCommas(line, idstr, synset);
        int id = stoi(idstr);

        if (id > maxId) maxId = id;
        if ((int)p_wordnet->idToSynset.size() <= id) p_wordnet->idToSynset.resize(id+1);

        p_wordnet->idToSynset[id] = synset;
        
        // split synset into nouns by spaces
        istringstream ss(synset);
        string noun;

        while (ss >> noun) {
            p_wordnet->nounToIds[noun].push_back(id);
            p_wordnet->nounSet.insert(noun);
        }
    }

    fin.close();

    int V = (int)p_wordnet->idToSynset.size();
    p_wordnet->G = new Digraph(V);

    ifstream fin2(hypernymsFile);
    if (!fin2) { 
        delete p_wordnet; 
        throw invalid_argument("cannot open hypernyms file"); 
    }
    
    // Read hypernyms
    while (getline(fin2, line)) {
        if (line.empty()) continue;

        istringstream ss(line);
        string token;

        if (!getline(ss, token, ',')) continue;

        int id = stoi(token);
        while (getline(ss, token, ',')) {
            int h = stoi(token);
            p_wordnet->G->addEdge(id, h);
        }
    }

    fin2.close();

    // Build SCA and validate rooted DAG in its constructor
    p_wordnet->sca = new ShortestCommonAncestor(*p_wordnet->G);
}

WordNet::~WordNet() { 
    delete p_wordnet; 
}

const unordered_set<string>& WordNet::nouns() const { 
    return p_wordnet->nounSet; 
}

bool WordNet::isNoun(const string& word) const {
    return p_wordnet->nounToIds.find(word) != p_wordnet->nounToIds.end();
}

string WordNet::sca(const string& noun1, const string& noun2) const {
    if (!isNoun(noun1) || !isNoun(noun2)) throw invalid_argument("not a noun");

    const auto& a = p_wordnet->nounToIds.at(noun1);
    const auto& b = p_wordnet->nounToIds.at(noun2);

    int anc = p_wordnet->sca->ancestorSubset(a, b);
    if (anc < 0) return string();

    return p_wordnet->idToSynset[anc];
}

int WordNet::distance(const string& noun1, const string& noun2) const {
    if (!isNoun(noun1) || !isNoun(noun2)) throw invalid_argument("not a noun");

    const auto& a = p_wordnet->nounToIds.at(noun1);
    const auto& b = p_wordnet->nounToIds.at(noun2);
    
    return p_wordnet->sca->lengthSubset(a, b);
}
