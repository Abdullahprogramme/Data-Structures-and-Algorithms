// Binary search tree range sum

#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

int rangeSumBST(Node* root, int low, int high) {
    if (root == nullptr) {
        return 0;
    }

    int sum = 0;

    if (root->key >= low && root->key <= high) {
        sum += root->key;
    }

    if (root->key > low) {
        sum += rangeSumBST(root->left, low, high);
    }

    if (root->key < high) {
        sum += rangeSumBST(root->right, low, high);
    }

    return sum;
}

int main() {
    // Example usage:
    Node* root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(7);
    root->left->left = new Node(2);
    root->left->right = new Node(4);
    root->right->left = new Node(6);
    root->right->right = new Node(8);

    // Test Case 1: Normal range
    cout << rangeSumBST(root, 4, 7) << endl; // Expected: 22
    // Test Case 2: Range includes all nodes
    cout << rangeSumBST(root, 1, 10) << endl; // Expected: 35 (sum of all nodes)
    // Test Case 3: Range includes single node
    cout << rangeSumBST(root, 5, 5) << endl; // Expected: 5
    // Test Case 4: Range outside tree values
    cout << rangeSumBST(root, 20, 30) << endl; // Expected: 0
    // Test Case 5: Empty tree
    cout << rangeSumBST(nullptr, 1, 10) << endl; // Expected: 0
    
    return 0;
}

// What is the time complexity of your solution in terms of:
// k = number of keys within the range [low,high]
// h = height of the tree

// The time complexity of the solution is O(h + k).
