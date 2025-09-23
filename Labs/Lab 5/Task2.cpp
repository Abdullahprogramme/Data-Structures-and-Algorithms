#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include "Task1.cpp"

using namespace std;

class BST {
    private:
        Node* root;

        int heightHelper(Node* node) {
            if (!node) return 0;

            int leftHeight = heightHelper(node->left);
            int rightHeight = heightHelper(node->right);

            return 1 + max(leftHeight, rightHeight);
        }

        int sizeOddHelper(Node* node) {
            if (!node) return 0;

            int count = (node->key % 2 != 0) ? 1 : 0;

            count += sizeOddHelper(node->left);
            count += sizeOddHelper(node->right);

            return count;
        }

    public:
        BST() : root(nullptr) {}

        ~BST() {
            function<void(Node*)> deleteTree = [&](Node* node) {
                if (!node) return;
                deleteTree(node->left);
                deleteTree(node->right);
                delete node;
            };

            deleteTree(root);
        }

        void setRoot(Node* r) { 
            root = r; 
        }

        // max depth of the tree
        int height() {
            return heightHelper(root);
        }

        // number of Nodes with an odd key
        int sizeOdd() {
            return sizeOddHelper(root);
        }

        // at each Node, do left and right subtrees have same height?
        bool isPerfectlyBalancedH() {
            function<bool(Node*)> helper = [&](Node* node) -> bool {
                if (!node) return true;

                int leftHeight = heightHelper(node->left);
                int rightHeight = heightHelper(node->right);

                if (leftHeight != rightHeight) return false;

                return helper(node->left) && helper(node->right);
            };

            return helper(root);
        }

        // is each Node semibalanced? that is, either a leaf or else size(larger child) / size (smaller child) ≤ 2
        bool isSemiBalancedI() {
            if (!root) return true;

            function<bool(Node*)> isSemiBalanced = [&](Node* node) -> bool {
                if (!node) return true;
                if (!node->left && !node->right) return true; // leaf node

                int leftHeight = heightHelper(node->left);
                int rightHeight = heightHelper(node->right);

                int larger = max(leftHeight, rightHeight);
                int smaller = min(leftHeight, rightHeight);

                if (smaller == 0) return false; // one child is missing, cannot divide

                if (larger / smaller > 2) return false;

                return isSemiBalanced(node->left) && isSemiBalanced(node->right);
            };

            return isSemiBalanced(root);
        }

        // number of nodes at a given depth
        int sizeAtDepth(int depth) {
            if (depth < 0) throw invalid_argument("Depth cannot be negative");

            function<int(Node*, int)> sizeAtDepthHelper = [&](Node* node, int currentDepth) -> int {
                if (!node) return 0;
                if (currentDepth == depth) return 1;

                return sizeAtDepthHelper(node->left, currentDepth + 1) + sizeAtDepthHelper(node->right, currentDepth + 1);
            };

            return sizeAtDepthHelper(root, 0);
        }

        // number of nodes whose depth is < a given depth
        int sizeAboveDepth(int depth) {
            if (depth < 0) throw invalid_argument("Depth cannot be negative");

            function<int(Node*, int)> sizeAboveDepthHelper = [&](Node* node, int currentDepth) -> int {
                if (!node || currentDepth >= depth) return 0;
                if (currentDepth < depth) return 1 + sizeAboveDepthHelper(node->left, currentDepth + 1) + sizeAboveDepthHelper(node->right, currentDepth + 1);

                return 0;
            };

            return sizeAboveDepthHelper(root, 0);
        }

        // number of nodes whose depth is > a given depth
        int sizeBelowDepth(int depth) {
            if (depth < 0) throw invalid_argument("Depth cannot be negative");

            function<int(Node*, int)> sizeBelowDepthHelper = [&](Node* node, int currentDepth) -> int {
                if (!node) return 0;
                if (currentDepth > depth) return 1 + sizeBelowDepthHelper(node->left, currentDepth + 1) + sizeBelowDepthHelper(node->right, currentDepth + 1);
                else return sizeBelowDepthHelper(node->left, currentDepth + 1) + sizeBelowDepthHelper(node->right, currentDepth + 1);
                return 0;
            };

            return sizeBelowDepthHelper(root, 0);
        }
};

int main() {
    vector<int> levelOrder = {7, 4, 12, 3, 6, 8, 1, 5, 10};

    Node* root = Level_Order_Constructor(levelOrder);

    BST tree;
    tree.setRoot(root);

    cout << "Height of tree: " << tree.height() << endl;
    cout << "Number of nodes with odd keys: " << tree.sizeOdd() << endl
            << "Is perfectly balanced: " << (tree.isPerfectlyBalancedH() ? "Yes" : "No") << endl
            << "Is semi balanced: " << (tree.isSemiBalancedI() ? "Yes" : "No") << endl;

    int depth = 2;
    cout << "Number of nodes at depth " << depth << ": " << tree.sizeAtDepth(depth) << endl;
    cout << "Number of nodes above depth " << depth << ": " << tree.sizeAboveDepth(depth) << endl;
    cout << "Number of nodes below depth " << depth << ": " << tree.sizeBelowDepth(depth) << endl;

    return 0;
}