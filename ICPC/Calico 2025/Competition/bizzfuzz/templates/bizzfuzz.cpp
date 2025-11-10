#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

bool isNumber(string& w) {
    for (auto& c : w) {
        if (!isdigit(c)) return false;
    }

    return true;
}

string converter(int w) {
    if (w % 3 == 0 && w % 5 == 0) return "bizzfuzz";
    else if (w % 3 == 0) return "bizz";
    else if (w % 5 == 0) return "fuzz";
    else return std::to_string(w);
}
/**
 * Return the string containing the word you should say
 * 
 * W1: the second-to-last word said
 * W2: the last word said
 */
string solve(string W1, string W2) {
    // YOUR CODE HERE

    if (!isNumber(W1) && !isNumber(W2)) return "crap";
    if (isNumber(W1) && isNumber(W2)) return converter(std::stoi(W2) + 1);

    if (isNumber(W1) && !isNumber(W2)) {
        int w1 = std::stoi(W1) + 2;
        return converter(w1);
    } else {
        int w2 = std::stoi(W2) + 1;
        return converter(w2);
    }
    
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        string W1, W2;
        cin >> W1 >> W2;
        cout << solve(W1, W2) << '\n';
    }
}
