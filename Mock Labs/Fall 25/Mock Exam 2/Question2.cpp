// BST validation and path sum

#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <functional>
#include <stdexcept>

using namespace std;

struct Node {
    int key;
    Node *left, *right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

bool isValidBST(Node* root) {
    function<bool(Node*, long long, long long)> validate = [&](Node* node, long long min, long long max) {
        if (!node) return true;

        if (node->key <= min || node->key >= max) return false;

        return validate(node->left, min, node->key) && validate(node->right, node->key, max);
    };

    return validate(root, numeric_limits<long long>::min(), numeric_limits<long long>::max());
}

bool hasPathSum(Node* root, int targetSum) {
    if (!root) return false;

    targetSum -= root->key;

    if (!root->left && !root->right) {
        return targetSum == 0;
    }

    return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
}

int main() {
    // Test Case 1: Valid BST
    //        5
    //      /   \
    //     3     7
    //    / \
    //   2   4
    Node* tree1 = new Node(5);
    tree1->left = new Node(3);
    tree1->right = new Node(7);
    tree1->left->left = new Node(2);
    tree1->left->right = new Node(4);

    cout << "Tree 1 is a valid BST: " << (isValidBST(tree1) ? "true" : "false") << endl;
    // isValidBST(tree1) should return true
    

    // Test Case 2: Invalid BST
    //        5
    //      /   \
    //     3     7
    //    / \
    //   2   6 <-- Invalid! 6 > 5 but in left subtree
    Node* tree2 = new Node(5);
    tree2->left = new Node(3);
    tree2->right = new Node(7);
    tree2->left->left = new Node(2);
    tree2->left->right = new Node(6);

    cout << "Tree 2 is a valid BST: " << (isValidBST(tree2) ? "true" : "false") << endl;
    // isValidBST(tree2) should return false

    cout << "-------------------------" << endl;


    Node* root = new Node(5);
    root->left = new Node(4);
    root->right = new Node(8);
    root->left->left = new Node(11);
    root->left->left->left = new Node(7);
    root->left->left->right = new Node(2);
    root->right->left = new Node(13);
    root->right->right = new Node(4);
    root->right->right->right = new Node(1);

    cout << hasPathSum(root, 22) << endl; // Expected: true
    cout << hasPathSum(root, 26) << endl; // Expected: true
    cout << hasPathSum(root, 10) << endl; // Expected: false
    cout << hasPathSum(nullptr, 0) << endl; // Expected: false (empty tree)
    
    // Single node tree
    Node* single = new Node(5);
    cout << hasPathSum(single, 5) << endl; // Expected: true
    cout << hasPathSum(single, 10) << endl; // Expected: false
}