#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("Birthday.in", "r", stdin);
    freopen("Birthday.out", "w", stdout);

    int N;
    cin >> N;
    unordered_map<string, pair<string, int>> birthday_map;
    
    for (int i = 0; i < N; ++i) {
        string name, date;
        int rating;
        cin >> name >> rating >> date;
        
        if ( birthday_map.find(date) == birthday_map.end()) {
            birthday_map[date] = {name, rating};
        } else {
            if (rating > birthday_map[date].second) {
                birthday_map[date] = {name, rating};
            }
        }
    }

    vector<string> result_names;
    for (const auto& entry : birthday_map) {
        result_names.push_back(entry.second.first);
    }

    sort(result_names.begin(), result_names.end());

    cout << result_names.size() << "\n";
    for (const string& name : result_names) {
        cout << name << "\n";
    }

    return 0;
}
