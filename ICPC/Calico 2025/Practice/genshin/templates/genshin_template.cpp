#include <cassert>
#include <iostream>

using namespace std;

int buy();
string wish();

/**
 * Starting with P primogems, get Baizhu through wishing without buying more
 * primogems than necessary.
 * 
 * Call the buy and wish functions below to make buy and wish queries. This
 * template handles parsing P and checking for CORRECT after you get Baizhu.
 * 
 * P: the number of starting primogems
 */
void solve(int P) {
    // YOUR CODE HERE
}

/**
 * Wish for a random item. Returns the name of the item you got.
 */
int buy() {
    cout << "buy" << endl;
    string temp;
    cin >> temp;
    if (temp == "WRONG_ANSWER") {
        exit(0);
    }
    int amount;
    cin >> temp >> amount >> temp;
    return amount;
}

/**
 * Wish for a random item. Returns the name of the item you got.
 */
string wish() {
    cout << "wish" << endl;
    string temp, item;
    cin >> temp;
    if (temp == "WRONG_ANSWER") {
        exit(0);
    }
    cin >> temp >> item;
    return item;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int P;
        cin >> P;
        solve(P);
        string temp;
        cin >> temp;
        if (temp == "WRONG_ANSWER") {
            exit(0);
        }
    }
}
