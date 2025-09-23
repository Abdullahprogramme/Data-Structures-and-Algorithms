// Template-based Binary Search Tree with Key, Value and operator[]
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace std;

/*
Time Complexities (Average / Worst Case):
--------------------------------------------------
insert(key, value):      O(log n) / O(n)
search(key):             O(log n) / O(n)
remove(key):             O(log n) / O(n)
findMin(), findMax():    O(log n) / O(n)
successor(key):          O(log n) / O(n)
operator[]:              O(log n) / O(n)
inorder_keys/values():   O(n)
clear():                 O(n)

n = number of nodes in the tree.
O(log n) is for balanced BST, O(n) for unbalanced (degenerate) BST.
*/

// BST template class
template <typename Key, typename Value>
class BST {
    public:
        struct Node {
            Key key;
            Value value;
            Node* left;
            Node* right;
            Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
        };

        BST() : root(nullptr) {}
        ~BST() { clear(root); }

        void insert(const Key& key, const Value& value) {
            root = insert(root, key, value);
        }

        bool search(const Key& key) const {
            return search(root, key);
        }

        void remove(const Key& key) {
            root = delete_node(root, key);
        }

        Node* findMin() const {
            Node* res = find_min(root);
            if (!res) throw runtime_error("BST is empty: no minimum.");
            return res;
        }

        Node* findMax() const {
            Node* res = find_max(root);
            if (!res) throw runtime_error("BST is empty: no maximum.");
            return res;
        }

        Node* successor(const Key& key) const {
            if (!root) throw runtime_error("BST is empty: no successor.");
            Node* res = successor(root, key);
            if (!res) {
                ostringstream oss;
                oss << "No successor found for key: " << key;
                throw runtime_error(oss.str());
            }
            return res;
        }

        vector<Key> inorder_keys() const {
            vector<Key> res;
            inorder_keys(root, res);
            return res;
        }
        vector<Value> inorder_values() const {
            vector<Value> res;
            inorder_values(root, res);
            return res;
        }

        // operator[] for getting/setting value by key
        Value& operator[](const Key& key) {
            Node* node = root;

            while (node) {
                if (key == node->key) return node->value;
                if (key < node->key) node = node->left;
                else node = node->right;
            }

            // If not found, insert default value
            if (!root) {
                root = new Node(key, Value());
                return root->value;
            }

            node = insert(root, key, Value());
            // Now find the node again
            while (node) {
                if (key == node->key) return node->value;
                if (key < node->key) node = node->left;
                else node = node->right;
            }
            
            throw runtime_error("operator[]: Unexpected error");
        }

        // Largest key in the BST less than or equal to val
        Key floor(const Key& val) {
            Node* node = root;
            Node* floorNode = nullptr;
            while (node) {
                if (node->key == val) {
                    return node->key;
                }

                if (node->key < val) {
                    floorNode = node;
                    node = node->right;
                } else {
                    node = node->left;
                }
            }

            if (!floorNode) {
                throw runtime_error("No floor key found.");
            }
            return floorNode->key;
        }

        // Smallest key in the BST greater than or equal to val
        Key ceil(const Key& val) {
            Node* node = root;
            Node* ceilNode = nullptr;
            while (node) {
                if (node->key == val) {
                    return node->key;
                }

                if (node->key > val) {
                    ceilNode = node;
                    node = node->left;
                } else {
                    node = node->right;
                }
            }

            if (!ceilNode) {
                throw runtime_error("No ceiling key found.");
            }
            return ceilNode->key;
        }

    private:
        Node* root;

        Node* insert(Node* node, const Key& key, const Value& value) {
            if (!node) return new Node(key, value);
            if (key < node->key)
                node->left = insert(node->left, key, value);
            else if (key > node->key)
                node->right = insert(node->right, key, value);
            else
                node->value = value; // update value if key exists
            return node;
        }

        bool search(Node* node, const Key& key) const {
            if (!node) return false;
            if (key == node->key) return true;
            if (key < node->key) return search(node->left, key);
            else return search(node->right, key);
        }

        Node* find_min(Node* node) const {
            if (!node) return nullptr;
            while (node->left) node = node->left;
            return node;
        }

        Node* find_max(Node* node) const {
            if (!node) return nullptr;
            while (node->right) node = node->right;
            return node;
        }

        Node* successor(Node* node, const Key& key) const {
            Node* succ = nullptr;
            while (node) {
                if (key < node->key) {
                    succ = node;
                    node = node->left;
                } else if (key > node->key) {
                    node = node->right;
                } else {
                    if (node->right) {
                        Node* minNode = find_min(node->right);
                        return minNode;
                    }
                    break;
                }
            }
            return succ;
        }

        Node* delete_node(Node* node, const Key& key) {
            if (!node) return nullptr;
            if (key < node->key) {
                node->left = delete_node(node->left, key);
            } else if (key > node->key) {
                node->right = delete_node(node->right, key);
            } else {
                if (!node->left) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (!node->right) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                } else {
                    Node* minNode = find_min(node->right);
                    node->key = minNode->key;
                    node->value = minNode->value;
                    node->right = delete_node(node->right, minNode->key);
                }
            }
            return node;
        }

        void inorder_keys(Node* node, vector<Key>& res) const {
            if (!node) return;
            inorder_keys(node->left, res);
            res.push_back(node->key);
            inorder_keys(node->right, res);
        }
        void inorder_values(Node* node, vector<Value>& res) const {
            if (!node) return;
            inorder_values(node->left, res);
            res.push_back(node->value);
            inorder_values(node->right, res);
        }

        void clear(Node* node) {
            if (!node) return;
            clear(node->left);
            clear(node->right);
            delete node;
        }
};

// Example usage
template class BST<int, string>; // Explicit instantiation for demonstration

int main() {
    BST<int, string> tree;
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");
    tree[7] = "seven";
    tree[12] = "twelve";
    tree[5] = "FIVE"; // update value

    cout << "Inorder keys: ";
    for (int k : tree.inorder_keys()) cout << k << " ";
    cout << endl;

    cout << "Inorder values: ";
    for (const auto& v : tree.inorder_values()) cout << v << " ";
    cout << endl;

    cout << "tree[7] = " << tree[7] << endl;
    cout << "tree[5] = " << tree[5] << endl;
    cout << "tree[12] = " << tree[12] << endl;

    try {
        cout << "Floor of 8: " << tree.floor(8) << endl; // should be 7
        cout << "Ceil of 8: " << tree.ceil(8) << endl;   // should be 10
        cout << "Floor of 12: " << tree.floor(12) << endl; // should be 12
        cout << "Ceil of 6: " << tree.ceil(6) << endl;   // should be 7
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
