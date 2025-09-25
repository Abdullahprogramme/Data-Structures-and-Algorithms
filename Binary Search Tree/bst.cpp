// C++ implementation of the Binary Search Tree using a class

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <functional>

using namespace std;

/*
Time Complexities (Average / Worst Case):
--------------------------------------------------
insert(val):             O(log n) / O(n)
search(val):             O(log n) / O(n)
remove(val):             O(log n) / O(n)
findMin(), findMax():    O(log n) / O(n)
successor(val):          O(log n) / O(n)
inorder/preorder/postorder: O(n)
clear():                 O(n)

n = number of nodes in the tree.
O(log n) is for balanced BST, O(n) for unbalanced (degenerate) BST.
*/

class BST {
    public:
        struct Node {
            int value;
            Node* left;
            Node* right;

            // Node constructor
            Node(int val) : value(val), left(nullptr), right(nullptr) {}
        };

        BST() : root(nullptr) {}
        ~BST() { clear(root); }

        // Public interface methods
        void insert(int val) { 
            root = insert(root, val); 
        }

        bool search(int val) { 
            return search(root, val); 
        }

        void remove(int val) { 
            root = delete_node(root, val); 
        }


        Node* findMin() {
            Node* res = find_min(root);
            if (!res) throw runtime_error("BST is empty: no minimum.");
            return res;
        }

        Node* findMax() {
            Node* res = find_max(root);
            if (!res) throw runtime_error("BST is empty: no maximum.");
            return res;
        }

        Node* successor(int val) {
            if (!root) throw runtime_error("BST is empty: no successor.");
            Node* res = successor(root, val);
            if (!res) {
                ostringstream oss;
                oss << "No successor found for value: " << val;
                throw runtime_error(oss.str());
            }
            return res;
        }

        vector<int> inorder() {
            vector<int> res;
            inorder(root, res);
            return res;
        }

        vector<int> preorder() {
            vector<int> res;
            preorder(root, res);
            return res;
        }
        
        vector<int> postorder() {
            vector<int> res;
            postorder(root, res);
            return res;
        }

        // Largest key in the BST less than or equal to val
        int floor(int val) {
            Node* node = root;
            int floorVal = -1; // Assuming all values are non-negative
            while (node) {
                if (node->value == val) {
                    return node->value;
                }

                if (node->value < val) {
                    floorVal = node->value;
                    node = node->right;
                } else {
                    node = node->left;
                }
            }

            if (floorVal == -1) {
                throw runtime_error("No floor value found.");
            }
            return floorVal;
        }

        // Smallest key in the BST greater than or equal to val
        int ceil(int val) {
            Node* node = root;
            int ceilVal = -1; // Assuming all values are non-negative
            while (node) {
                if (node->value == val) {
                    return node->value;
                }

                if (node->value > val) {
                    ceilVal = node->value;
                    node = node->left;
                } else {
                    node = node->right;
                }
            }

            if (ceilVal == -1) {
                throw runtime_error("No ceiling value found.");
            }
            return ceilVal;
        }

        int select(int k) {
            if (k < 0 || k >= inorder().size()) {
                throw out_of_range("Index out  of range in select()");
            }

            function<int(Node*)> subtree_size = [&](Node* node) -> int {
                if (!node) return 0;
                return 1 + subtree_size(node->left) + subtree_size(node->right);
            };

            // int subtree_size = [&](Node* node) -> int {
            //     if (!node) return 0;
            //     return 1 + subtree_size(node->left) + subtree_size(node->right);
            // };

            function<int(Node*, int)> select_helper = [&](Node* node, int k) -> int {
                if (!node) throw runtime_error("Unexpected null node in select_helper");
                int size_left = subtree_size(node->left);
                if (size_left > k) {
                    return select_helper(node->left, k);
                } else if (size_left < k) {
                    return select_helper(node->right, k - size_left - 1);
                } else {
                    return node->value;
                }
            };

            return select_helper(root, k);
        }

    private:
        Node* root;

        Node* insert(Node* node, int val) {
            if (!node) return new Node(val);
            if (val < node->value)
                node->left = insert(node->left, val);
            else
                node->right = insert(node->right, val);
            return node;
        }

        bool search(Node* node, int val) {
            if (!node) return false;
            if (node->value == val) return true;
            if (val < node->value) return search(node->left, val);
            else return search(node->right, val);
        }

        Node* find_min(Node* node) {
            if (!node) return nullptr;
            while (node->left) node = node->left;
            return node;
        }

        Node* find_max(Node* node) {
            if (!node) return nullptr;
            while (node->right) node = node->right;
            return node;
        }

        Node* successor(Node* node, int val) {
            Node* succ = nullptr;
            while (node) {
                if (val < node->value) {
                    succ = node;
                    node = node->left;
                } else if (val > node->value) {
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

        Node* delete_node(Node* node, int val) {
            if (!node) return nullptr;
            if (val < node->value) {
                node->left = delete_node(node->left, val);
            } else if (val > node->value) {
                node->right = delete_node(node->right, val);
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
                    node->value = minNode->value;
                    node->right = delete_node(node->right, minNode->value);
                }
            }
            return node;
        }

        void inorder(Node* node, vector<int>& res) {
            if (!node) return;
            inorder(node->left, res);
            res.push_back(node->value);
            inorder(node->right, res);
        }

        void preorder(Node* node, vector<int>& res) {
            if (!node) return;
            res.push_back(node->value);
            preorder(node->left, res);
            preorder(node->right, res);
        }

        void postorder(Node* node, vector<int>& res) {
            if (!node) return;
            postorder(node->left, res);
            postorder(node->right, res);
            res.push_back(node->value);
        }

        void clear(Node* node) {
            if (!node) return;
            clear(node->left);
            clear(node->right);
            delete node;
        }
};

int main() {
    BST tree;
    tree.insert(20);
    tree.insert(5);
    tree.insert(2);
    tree.insert(9);
    tree.insert(12);
    tree.insert(15);
    tree.insert(19);
    tree.insert(13);
    tree.insert(17);

    vector<int> in = tree.inorder();
    for (int v : in) cout << v << " ";
    cout << endl;

    cout << "Floor of 16: " << tree.floor(16) << endl; // should be 15
    cout << "Ceil of 16: " << tree.ceil(16) << endl;   // should be 17

    try {
        BST::Node* s1 = tree.successor(12);
        cout << "Successor of 12: " << s1->value << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    try {
        BST::Node* s2 = tree.successor(13);
        cout << "Successor of 13: " << s2->value << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    try {
        BST::Node* s3 = tree.successor(19);
        cout << "Successor of 19: " << s3->value << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    
    try {
        BST::Node* s4 = tree.successor(20);
        cout << "Successor of 20: " << s4->value << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Demonstrate findMin and findMax exception
    try {
        BST emptyTree;
        emptyTree.findMin();
    } catch (const exception& e) {
        cout << "findMin on empty: " << e.what() << endl;
    }
    try {
        BST emptyTree;
        emptyTree.findMax();
    } catch (const exception& e) {
        cout << "findMax on empty: " << e.what() << endl;
    }

    return 0;
}
   