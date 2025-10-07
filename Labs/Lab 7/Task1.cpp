#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include "red-black-bst.hpp"

using namespace std;

// O(n) time complexity
int countInRange1(RedBlackBST<int, string>& tree, int low, int high) {

    function<void(RedBlackBST<int, string>::Node*, vector<int>&)> inOrder = [&](RedBlackBST<int, string>::Node* node, vector<int>& keys) {
        if (node == nullptr) return;
        inOrder(node->left, keys);
        keys.push_back(node->key);
        inOrder(node->right, keys);
    };

    vector<int> keys;
    inOrder(tree.root, keys);

    // Count keys in the specified range
    return count_if(keys.begin(), keys.end(), [&](int key) {
        return key >= low && key <= high;
    });
}

// O(log n) time complexity
int countInRange2(RedBlackBST<int, string>& tree, int low, int high) {
    if (low > high) return 0;
    return tree.rank(high + 1) - tree.rank(low);
}

int main() {
    RedBlackBST<int, string> tree;
    tree.put(30, "thirty"); 
    tree.put(10, "ten");
    tree.put(40, "forty");
    tree.put(20, "twenty");
    tree.put(50, "fifty");
    tree.put(35, "thirty-five");

    int low = 15, high = 35;
    cout << "Count in range [" << low << ", " << high << "] using O(n) method: " 
         << countInRange1(tree, low, high) << endl;
    cout << "Count in range [" << low << ", " << high << "] using O(log n) method: " 
         << countInRange2(tree, low, high) << endl;

    return 0;
}