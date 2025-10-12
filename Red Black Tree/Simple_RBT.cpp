#pragma once

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

template<typename Key, typename Value>
class RedBlackBST {
    static constexpr bool RED = true;
    static constexpr bool BLACK = false;
    
public:
    // BST helper node data type
    struct Node {
        Key key;             // key
        Value val;           // associated data
        Node* left;          // left subtree
        Node* right;         // right subtree
        bool color;          // color of the parent link
        int size;            // size of the subtree rooted at this node

        Node(const Key& k, const Value& v, bool c, int s) 
            : key(k), val(v), color(c), size(s), left(nullptr), right(nullptr) {}
    };

    Node* root; // root of the BST

public:
    // Constructor to initialize an empty tree
    RedBlackBST() : root(nullptr) {}

private:
    // Helper methods
    bool isRed(Node* x) const {
        return x != nullptr && x->color == RED;
    }

    int size(Node* x) const {
        return x == nullptr ? 0 : x->size;
    }

public:
    int size() const {
        return size(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    // Standard BST search
    Value get(const Key& key) const {
        Node* x = root;
        while (x != nullptr) {
            if (key < x->key) {
                x = x->left;
            } else if (key > x->key) {
                x = x->right;
            } else {
                return x->val;
            }
        }
        throw std::out_of_range("Key not found");
    }

    bool contains(const Key& key) const {
        try {
            get(key);
            return true;
        } catch (...) {
            return false;
        }
    }

    // Insert key-value pair into the tree
    void put(const Key& key, const Value& val) {
        root = put(root, key, val);
        root->color = BLACK;
    }

private:
    Node* put(Node* h, const Key& key, const Value& val) {
        if (h == nullptr) return new Node(key, val, RED, 1);

        if (key < h->key) {
            h->left = put(h->left, key, val);
        } else if (key > h->key) {
            h->right = put(h->right, key, val);
        } else {
            h->val = val;
        }

        // Balance the tree
        if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
        if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
        if (isRed(h->left) && isRed(h->right)) flipColors(h);

        h->size = size(h->left) + size(h->right) + 1;
        return h;
    }

    // Rotations and color flipping
    Node* rotateLeft(Node* h) {
        assert(h != nullptr && isRed(h->right));
        Node* x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = size(h->left) + size(h->right) + 1;
        return x;
    }

    Node* rotateRight(Node* h) {
        assert(h != nullptr && isRed(h->left));
        Node* x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = size(h->left) + size(h->right) + 1;
        return x;
    }

    void flipColors(Node* h) {
       // assert(h != nullptr);
      //  assert(isRed(h->left) && isRed(h->right));
        h->color = RED;
        h->left->color = BLACK;
        h->right->color = BLACK;
    }

public:
    void removeMin() {
        if (isEmpty()) throw std::out_of_range("Tree is empty");
        if (!isRed(root->left) && !isRed(root->right)) root->color = RED;
        root = removeMin(root);
        if (!isEmpty()) root->color = BLACK;
    }

    void removeMax() {
        if (isEmpty()) throw std::out_of_range("Tree is empty");
        if (!isRed(root->left) && !isRed(root->right)) root->color = RED;
        root = removeMax(root);
        if (!isEmpty()) root->color = BLACK;
    }

    void remove(const Key& key) {
        if (!contains(key)) throw std::out_of_range("Key not found");
        if (!isRed(root->left) && !isRed(root->right)) root->color = RED;
        root = remove(root, key);
        if (!isEmpty()) root->color = BLACK;
    }

private:
    Node* removeMin(Node* h) {
        if (h->left == nullptr) return nullptr;
        if (!isRed(h->left) && !isRed(h->left->left)) h = moveRedLeft(h);
        h->left = removeMin(h->left);
        return balance(h);
    }

    Node* removeMax(Node* h) {
        if (isRed(h->left)) h = rotateRight(h);
        if (h->right == nullptr) return nullptr;
        if (!isRed(h->right) && !isRed(h->right->left)) h = moveRedRight(h);
        h->right = removeMax(h->right);
        return balance(h);
    }

    Node* remove(Node* h, const Key& key) {
        if (key < h->key) {
            if (!isRed(h->left) && !isRed(h->left->left)) h = moveRedLeft(h);
            h->left = remove(h->left, key);
        } else {
            if (isRed(h->left)) h = rotateRight(h);
            if (key == h->key && h->right == nullptr) return nullptr;
            if (!isRed(h->right) && !isRed(h->right->left)) h = moveRedRight(h);
            if (key == h->key) {
                Node* x = min(h->right);
                h->key = x->key;
                h->val = x->val;
                h->right = removeMin(h->right);
            } else {
                h->right = remove(h->right, key);
            }
        }
        return balance(h);
    }

    Node* moveRedLeft(Node* h) {
        flipColors(h);
        if (isRed(h->right->left)) {
            h->right = rotateRight(h->right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    Node* moveRedRight(Node* h) {
        flipColors(h);
        if (isRed(h->left->left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    Node* balance(Node* h) {
        if (isRed(h->right)) h = rotateLeft(h);
        if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
        if (isRed(h->left) && isRed(h->right)) flipColors(h);
        h->size = size(h->left) + size(h->right) + 1;
        return h;
    }

    Node* min(Node* h) const {
        if (h->left == nullptr) return h;
        return min(h->left);
    }

public:
    void keys(std::vector<Key>& keys) {
        keys.clear();
        inOrder(root, keys);
    }

private:
    void inOrder(Node* h, std::vector<Key>& keys) const {
        if (h == nullptr) return;
        inOrder(h->left, keys);
        keys.push_back(h->key);
        inOrder(h->right, keys);
    }



/***************************************************************************
    *  Utility functions.
    ***************************************************************************/

    public:
    /**
     * Returns the height of the BST (for debugging).
     * return the height of the BST (a 1-node tree has height 0)
     */
    int height() {
        return height(root);
    }

    private:
    int height(Node* x) {
        if (x == nullptr) return -1;
        return 1 + std::max(height(x->left), height(x->right));
    }

   /***************************************************************************
    *  Ordered symbol table methods.
    ***************************************************************************/

   public:
    /**
     * Returns the smallest key in the symbol table.
     * @return the smallest key in the symbol table
     */
    Key min() {
        if (isEmpty()) throw std::out_of_range("calls min() with empty symbol table");
        return min(root)->key;
    }

    private:
    // the smallest key in subtree rooted at x; nullptr if no such key
    Node* min(Node* x) {
        // assert x != nullptr;
        if (x->left == nullptr) return x;
        else                    return min(x->left);
    }

    public:
    /**
     * Returns the largest key in the symbol table.
     * return the largest key in the symbol table
     */
    Key max() {
        if (isEmpty()) throw std::out_of_range("calls max() with empty symbol table");
        return max(root)->key;
    }

    private:
    // the largest key in the subtree rooted at x; nullptr if no such key
    Node* max(Node* x) {
        // assert x != nullptr;
        if (x->right == nullptr) return x;
        else                     return max(x->right);
    }

    public:
    /**
     * Returns the largest key in the symbol table less than or equal to key.
     * key: the key
     * return the largest key in the symbol table less than or equal to key
     */
    Key floor(const Key& key) {
        if (isEmpty()) throw std::out_of_range("calls floor() with empty symbol table");
        Node* x = floor(root, key);
        if (x == nullptr) throw std::out_of_range("argument to floor() is too small");
        else              return x->key;
    }

    private:
    // the largest key in the subtree rooted at x less than or equal to the given key
    Node* floor(Node* x, const Key& key) {
        if (x == nullptr) return nullptr;
        int cmp = key.compareTo(x.key);
        if (key == x->key) return x;
        if (key  < x->key)  return floor(x->left, key);
        Node* t = floor(x->right, key);
        if (t != nullptr) return t;
        else              return x;
    }

    public:
    /**
     * Returns the smallest key in the symbol table greater than or equal to key.
     * key: the key
     * return the smallest key in the symbol table greater than or equal to key
     */
    Key ceiling(const Key& key) {
        if (isEmpty()) throw std::out_of_range("calls ceiling() with empty symbol table");
        Node* x = ceiling(root, key);
        if (x == nullptr) throw std::out_of_range("argument to ceiling() is too large");
        else              return x->key;
    }

    private:
    // the smallest key in the subtree rooted at x greater than or equal to the given key
    Node* ceiling(Node* x, const Key& key) {
        if (x == nullptr) return nullptr;
        int cmp = key.compareTo(x.key);
        if (key == x->key) return x;
        if (x->key > key)  return ceiling(x->right, key);
        Node* t = ceiling(x->left, key);
        if (t != nullptr) return t;
        else              return x;
    }

    public:
    /**
     * Return the key in the symbol table of a given rank.
     * This key has the property that there are rank keys in
     * the symbol table that are smaller. In other words, this key is the
     * (rank+1)st smallest key in the symbol table.
     *
     * rank: the order statistic
     * return the key in the symbol table of given rank
          */
    Key select(int rank) {
        if (rank < 0 || rank >= size()) {
            throw std::out_of_range("argument to select() is invalid: " + rank);
        }
        return select(root, rank);
    }

    private:
    // Return key in BST rooted at x of given rank.
    // Precondition: rank is in legal range.
    Key select(Node* x, int rank) {
        if (x == nullptr) throw std::out_of_range("argument to select() is invalid");
        int leftSize = size(x->left);
        if      (leftSize > rank) return select(x->left,  rank);
        else if (leftSize < rank) return select(x->right, rank - leftSize - 1);
        else                      return x->key;
    }

    public:
    /**
     * Return the number of keys in the symbol table strictly less than {@code key}.
     * key: the key
     * return the number of keys in the symbol table strictly less than {@code key}
     */
    int rank(const Key& key) {
        return rank(key, root);
    }

    private:
    // number of keys less than key in the subtree rooted at x
    int rank(const Key& key, Node* x) {
        if (x == nullptr) return 0;

        if      (key < x->key) return rank(key, x->left);
        else if (x->key < key) return 1 + size(x->left) + rank(key, x->right);
        else                   return size(x->left);
    }


    private:
   /***************************************************************************
    *  Check integrity of red-black tree data structure.
    ***************************************************************************/
    bool check() {
        if (!isBST())            std::cerr << "Not in symmetric order";
        if (!isSizeConsistent()) std::cerr << "Subtree counts not consistent";
        if (!isRankConsistent()) std::cerr << "Ranks not consistent";
        if (!is23())             std::cerr << "Not a 2-3 tree";
        if (!isBalanced())       std::cerr << "Not balanced";
        return isBST() && isSizeConsistent() && isRankConsistent() && is23() && isBalanced();
    }

    // does this binary tree satisfy symmetric order?
    // Note: this test also ensures that data structure is a binary tree since order is strict
    bool isBST() {
        return isBST(root, min(), max());
    }

    // is the tree rooted at x a BST 
    bool isBST(Node* x) {
        if (x == nullptr) return true;
        return isBST_max(x->left, x->key) && isBST_min(x->right, x->key);
    }

    // is the tree rooted at x a BST with all keys strictly greater than min
    bool isBST_min(Node* x, const Key& min) {
        if (x == nullptr) return true;
        if (x.key <= min) return false;
        return isBST_min_max(x->left, min, x->key) && isBST_min(x->right, x->key);
    }

    // is the tree rooted at x a BST with all keys strictly smaller than max
    bool isBST_max(Node* x, const Key& max) {
        if (x == nullptr) return true;
        if (x.key >= max) return false;
        return isBST_max(x->left, x->key) && isBST_min_max(x->right, x->key, max);
    }

    // is the tree rooted at x a BST with all keys strictly between min and max
    bool isBST_min_max(Node* x, const Key& min, const Key& max) {
        if (x == nullptr) return true;
        if (x.key <= min) return false;
        if (x.key >= max) return false;
        return isBST_min_max(x->left, min, x->key) && isBST_min_max(x->right, x->key, max);
    }

    // are the size fields correct?
    bool isSizeConsistent() { return isSizeConsistent(root); }
    bool isSizeConsistent(Node* x) {
        if (x == nullptr) return true;
        if (x->size != size(x->left) + size(x->right) + 1) return false;
        return isSizeConsistent(x->left) && isSizeConsistent(x->right);
    }

    // check that ranks are consistent
    bool isRankConsistent() {
        for (int i = 0; i < size(); i++)
            if (i != rank(select(i))) return false;
        for (Key key : keys())
            if (key != select(rank(key))) return false;
        return true;
    }

    // Does the tree have no red right links, and at most one (left)
    // red links in a row on any path?
    bool is23() { return is23(root); }
    bool is23(Node* x) {
        if (x == nullptr) return true;
        if (isRed(x->right)) return false;
        if (x != root && isRed(x) && isRed(x->left))
            return false;
        return is23(x->left) && is23(x->right);
    }

    // do all paths from root to leaf have same number of black edges?
    bool isBalanced() {
        int black = 0;     // number of black links on path from root to min
        Node* x = root;
        while (x != nullptr) {
            if (!isRed(x)) black++;
            x = x->left;
        }
        return isBalanced(root, black);
    }

    // does every path from the root to a leaf have the given number of black links?
    bool isBalanced(Node* x, int black) {
        if (x == nullptr) return black == 0;
        if (!isRed(x)) black--;
        return isBalanced(x->left, black) && isBalanced(x->right, black);
    }

};
