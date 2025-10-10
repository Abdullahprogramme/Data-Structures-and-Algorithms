#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("notlast.in", "r", stdin);
    freopen("notlast.out", "w", stdout);

    int N;
    cin >> N;

    unordered_map<string, int> milkProduction = {
        {"Bessie", 0},
        {"Elsie", 0},
        {"Daisy", 0},
        {"Gertie", 0},
        {"Annabelle", 0},
        {"Maggie", 0},
        {"Henrietta", 0}
    };

    for (int i = 0; i < N; ++i) {
        string name;
        int amount;
        cin >> name >> amount;
        milkProduction[name] += amount;
    }

    set<int> uniqueAmounts;
    for (const auto& entry : milkProduction) {
        uniqueAmounts.insert(entry.second);
    }

    if (uniqueAmounts.size() == 1) {
        cout << "Tie\n";
        return 0;
    }

    int secondMin = *next(uniqueAmounts.begin());

    vector<string> candidates;
    for (const auto& entry : milkProduction) {
        if (entry.second == secondMin) {
            candidates.push_back(entry.first);
        }
    }

    if (candidates.size() == 1) {
        cout << candidates[0] << "\n";
    } else {
        cout << "Tie\n";
    }

    return 0;
}
