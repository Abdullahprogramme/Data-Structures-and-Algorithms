#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>

using namespace std;

struct BSTnode {
    double key;
    char value;
    BSTnode *left;
    BSTnode *right;
    int size; // Size of subtree

    BSTnode(double k, char val) : key(k), value(val), left(nullptr), right(nullptr), size(1) {}
};

class Mstring {
    private:
        BSTnode* root;

        // Update size of a node based on its children
        void updateSize(BSTnode* node) {
            if (node == nullptr) return;
            node->size = 1;
            if (node->left) node->size += node->left->size;
            if (node->right) node->size += node->right->size;
        }

        // Insert a node with given key and value
        BSTnode* insertHelper(BSTnode* node, double key, char value) {
            if (node == nullptr) {
                return new BSTnode(key, value);
            }

            if (key < node->key) {
                node->left = insertHelper(node->left, key, value);
            } else if (key > node->key) {
                node->right = insertHelper(node->right, key, value);
            } else {
                // Key already exists, update value
                node->value = value;
                return node;
            }

            updateSize(node);
            return node;
        }

        // Select the i-th node (0-indexed) in inorder traversal
        BSTnode* select(BSTnode* node, int i) const {
            if (node == nullptr) return nullptr;

            int leftSize = (node->left) ? node->left->size : 0;

            if (i == leftSize) {
                return node;
            } else if (i < leftSize) {
                return select(node->left, i);
            } else {
                return select(node->right, i - leftSize - 1);
            }
        }

        // Get all nodes in inorder traversal
        void inorderTraversal(BSTnode* node, vector<BSTnode*>& nodes) const {
            if (node == nullptr) return;
            inorderTraversal(node->left, nodes);
            nodes.push_back(node);
            inorderTraversal(node->right, nodes);
        }

        BSTnode* removeHelper(BSTnode* node, double key) {
            if (node == nullptr) return node;

            if (key < node->key) {
                node->left = removeHelper(node->left, key);
            } else if (key > node->key) {
                node->right = removeHelper(node->right, key);
            } else {
                // Node with only one child or no child
                if (node->left == nullptr) {
                    BSTnode* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    BSTnode* temp = node->left;
                    delete node;
                    return temp;
                }

                // Node with two children: Get the inorder successor
                BSTnode* temp = node->right;
                while (temp && temp->left != nullptr) {
                    temp = temp->left;
                }
                node->key = temp->key;
                node->value = temp->value;

                // Delete the inorder successor
                node->right = removeHelper(node->right, temp->key);
            }

            updateSize(node);
            return node;
        }

        // Recursively delete all nodes
        void deleteTree(BSTnode* node) {
            if (node == nullptr) return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }

    public:
        Mstring() {
            // Initialize with dummy nodes at beginning (key=0) and end (key=1)
            root = new BSTnode(0.0, '\0'); // dummy start
            root = insertHelper(root, 1.0, '\0'); // dummy end
        }

        ~Mstring() { 
            deleteTree(root);
        }

        char get(int i) const {
            // Get the (i+1)th node since we have a dummy at position 0
            BSTnode* node = select(root, i + 1);
            if (node != nullptr && node->key != 1.0) { // Not the end dummy
                return node->value;
            }
            throw out_of_range("Index out of range");
        }

        void insert(int i, char c) {
            vector<BSTnode*> nodes;
            inorderTraversal(root, nodes);
            
            // Find the position to insert (i+1 because of dummy at start)
            int insertPos = i + 1;
            
            if (insertPos < 0 || insertPos > (int)nodes.size() - 1) {
                throw out_of_range("Index out of range");
            }
            
            double newKey;
            if (insertPos == 0) {
                // Insert at the very beginning (should not happen due to dummy)
                newKey = nodes[0]->key / 2.0;
            } else if (insertPos == nodes.size() - 1) {
                // Insert at the end (before the dummy end)
                newKey = (nodes[insertPos - 1]->key + nodes[insertPos]->key) / 2.0;
            } else {
                // Insert in the middle
                newKey = (nodes[insertPos - 1]->key + nodes[insertPos]->key) / 2.0;
            }
            
            root = insertHelper(root, newKey, c);
        }

        void remove(int i) {
            // Remove the (i+1)th node since we have a dummy at position 0
            BSTnode* node = select(root, i + 1);
            if (node != nullptr && node->key != 0.0 && node->key != 1.0) {
                root = removeHelper(root, node->key);
            } else {
                throw out_of_range("Index out of range or trying to remove dummy node");
            }
        }

        void print() const {
            vector<BSTnode*> nodes;
            inorderTraversal(root, nodes);
            
            // Skip the first and last dummy nodes
            for (int i = 1; i < (int)nodes.size() - 1; i++) {
                cout << nodes[i]->value;
            }
            cout << endl;
        }

        int size() const {
            // Total size minus the two dummy nodes
            return (root ? root->size : 0) - 2;
        }
};

int main() {
    Mstring s;
    
    try {
        // Insert characters to form "abcd"
        s.insert(0, 'a'); s.insert(1, 'b'); s.insert(2, 'c'); s.insert(3, 'd');
        cout << "String after inserts: "; s.print(); // Expected: abcd

        // Get a character
        cout << "s.get(2) = " << s.get(2) << endl; // Expected: c

        // Insert in the middle
        s.insert(2, 'X');
        cout << "After insert X at pos 2: "; s.print(); // Expected: abXcd

        // Remove a character
        s.remove(3);
        cout << "After remove at pos 3: "; s.print(); // Expected: abXd

        // Remove first and last
        s.remove(0); 
        if (s.size() > 0) s.remove(s.size() - 1);
        cout << "After removing first and last: "; s.print(); // Expected: bX
        
        cout << "Final string size: " << s.size() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}