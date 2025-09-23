#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    string s, t;    
    cin >> s >> t;

    vector<char> stack;
    int t_len = t.length();

    for (char c : s) {
        stack.push_back(c);
        if (stack.size() >= t_len && string(stack.end() - t_len, stack.end()) == t) {
            stack.resize(stack.size() - t_len);
        }
    }

    for (char c : stack) {
        printf("%c", c);
    }
    
    return 0;
}