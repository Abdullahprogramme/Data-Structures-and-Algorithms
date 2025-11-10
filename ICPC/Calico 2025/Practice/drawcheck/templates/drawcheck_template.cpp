#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

vector<int> draw();
string check(int);

/*
 * Find the number on the judge's card through draw and check queries while
 * minimizing the average number of queries needed.
 * 
 * Call the draw and check functions below to make draw and check queries. Return
 * from this function when you see check() return ABSENT. This template also
 * handles reading the final verdict at the end.
*/
void solve() {
    // YOUR CODE HERE
}

/*
 * Shuffle the deck and draw the top 17 cards.
 */
vector<int> draw() {
    cout << "draw" << endl;
    int K = 17;
    vector<int> cards(K);
    for (int &x: cards) {
        cin >> x;
    }
    return cards;
}

/*
 * Check if a card exists within the deck.
 */
string check(int card) {
    cout << "check " << card << endl;
    string result;
    cin >> result;
    return result;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
    string temp;
    cin >> temp;
}
