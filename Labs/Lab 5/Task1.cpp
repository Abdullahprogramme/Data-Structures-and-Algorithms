#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* Level_Order_Constructor(const vector<int>& levelOrder) {
    if (levelOrder.empty()) return nullptr;

    queue<tuple<Node*, int, int>> Queue;

    // creating the root node
    Node* root = new Node(levelOrder[0]);
    Queue.push({root, INT_MIN, INT_MAX});

    int i = 1; // index for next element to process

    while(!Queue.empty() && i < levelOrder.size()) {
        auto [currentNode, minVal, maxVal] = Queue.front();
        Queue.pop();

        // Left child
        if (i < levelOrder.size() && levelOrder[i] > minVal && levelOrder[i] < currentNode->key) {
            Node* leftChild = new Node(levelOrder[i]);
            Queue.push({leftChild, minVal, currentNode->key});
            currentNode->left = leftChild;
            ++i;
        }

        // Right child
        if (i < levelOrder.size() && levelOrder[i] > currentNode->key && levelOrder[i] < maxVal) {
            Node* rightChild = new Node(levelOrder[i]);
            Queue.push({rightChild, currentNode->key, maxVal});
            currentNode->right = rightChild;
            i++;
        }
    }

    return root;
}


vector<int> Level_Order_Traversal(Node* root) {
    if (!root) return {};

    queue<Node*> Queue;
    vector<int> result;

    Queue.push(root);
    while (!Queue.empty()) {
        Node* currentNode = Queue.front();
        Queue.pop();

        result.push_back(currentNode->key);

        if (currentNode->left) Queue.push(currentNode->left);
        if (currentNode->right) Queue.push(currentNode->right);
    }

    return result;
}

// int main() {
//     vector<int> levelOrder = {7, 4, 12, 3, 6, 8, 1, 5, 10};

//     Node* root = Level_Order_Constructor(levelOrder);
//     vector<int> traversalResult = Level_Order_Traversal(root);

//     cout << "Level Order Traversal: ";
//     for_each(traversalResult.begin(), traversalResult.end(), [](int val) {
//         cout << val << " ";
//     });

//     cout << endl;

//     return 0;
// }