// Red-Black Tree Implementation in C++ having 2-node and 3-node insertions

#include <iostream>
#include <stdexcept>
#include <vector>

/*
Operations:
1. Insertion (2-node and 3-node)
2. Deletion
3. Search
4. Traversals (Inorder, Preorder, Postorder, Level-order)
*/

using namespace std;

class RBT {
    public:
        RBT();
        ~RBT();

        // Insertion
        void insert(int key);
        // Deletion
        void remove(int key);
        // Search
        bool search(int key);
        // Traversals
        void inorder();
        void preorder();
        void postorder();
        void levelOrder();

    private:
        struct Node {
            int data;
            bool color; // 0 for Red, 1 for Black
            Node *left, *right, *parent;

            Node(int data) : data(data), color(0), left(nullptr), right(nullptr), parent(nullptr) {}
        };

        Node *root;

        // Helper functions
        void rotateLeft(Node *&node);
        void rotateRight(Node *&node);
        void fixViolation(Node *&node);
        void inorderHelper(Node *node);
        void preorderHelper(Node *node);
        void postorderHelper(Node *node);
        void levelOrderHelper(Node *node);
};