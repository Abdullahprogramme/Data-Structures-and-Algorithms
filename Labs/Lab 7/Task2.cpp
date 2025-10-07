#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <limits>
#include "red-black-bst.hpp"

using namespace std;

// O(n) time complexity
int findClosestKey1(RedBlackBST<int, string>& tree, int target) {

    function<void(RedBlackBST<int, string>::Node*, vector<int>&)> inOrder = [&](RedBlackBST<int, string>::Node* node, vector<int>& keys) {
        if (node == nullptr) return;
        inOrder(node->left, keys);
        keys.push_back(node->key);
        inOrder(node->right, keys);
    };

    vector<int> keys;
    inOrder(tree.root, keys);

    // Find the closest key
    return keys.empty() ? -1 : *min_element(keys.begin(), keys.end(), [&](int a, int b) {
        return abs(a - target) < abs(b - target);
    });
}

// O(log n) time complexity
int findClosestKey2(RedBlackBST<int, string>& tree, int target) {
    int closest = -1;
    int minDiff = numeric_limits<int>::max();

    function<void(RedBlackBST<int, string>::Node*)> findClosest = [&](RedBlackBST<int, string>::Node* node) {
        if (node == nullptr) return;
        int diff = abs(node->key - target);
        if (diff < minDiff) {
            minDiff = diff;
            closest = node->key;
        }
        if (node->key < target) {
            findClosest(node->right);
        } else {
            findClosest(node->left);
        }
    };

    findClosest(tree.root);
    return closest;
}

int main() {
    RedBlackBST<int, string> tree;
    tree.put(30, "thirty"); 
    tree.put(10, "ten");
    tree.put(40, "forty");
    tree.put(20, "twenty");
    tree.put(50, "fifty");
    tree.put(35, "thirty-five");
    tree.put(31, "thirty-one");

    int target = 33;
    cout << "Closest key to " << target << " using O(n) method: " 
         << findClosestKey1(tree, target) << endl;
    cout << "Closest key to " << target << " using O(log n) method: " 
         << findClosestKey2(tree, target) << endl;

    return 0;
}