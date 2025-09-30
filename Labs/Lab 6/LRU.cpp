#include "Svector.hpp"
#include <list>
#include <map>
#include <stdexcept>
#include <iostream>

using namespace std;

class LRU {
    private:
        size_t capacity;
        list<int> keys;  // Doubly linked list
        map<int, list<int>::iterator> iterators;  // Symbol table: item -> iterator to its position in the list
        map<int, Svector> cache;  // Symbol table: item -> its value

    public:
        LRU(size_t cap = 10) : capacity(cap) {}

        bool empty() const {
            return cache.empty();
        }

        int size() const {
            return cache.size();
        }

        void access(int item) {
            auto cache_it = cache.find(item);
            if (cache_it == cache.end()) {
                // Item not found, insert it
                if (cache.size() >= capacity) {
                    // Remove the least recently used
                    int lru_key = keys.back();
                    keys.pop_back();
                    cache.erase(lru_key);
                    iterators.erase(lru_key);
                }

                // Insert the new item at the front (most recent)
                cache[item] = Svector();
                keys.push_front(item);
                iterators[item] = keys.begin();
            } else {
                // Item found, move it to the front
                auto iter_it = iterators.find(item);
                if (iter_it != iterators.end()) {
                    // Remove from current position
                    keys.erase(iter_it->second);
                    keys.push_front(item);
                    iterators[item] = keys.begin();
                }
            }
        }

        int remove() {
            if (cache.empty()) {
                throw runtime_error("Cache is empty");
            }

            // Remove the least recently used item
            int lru_key = keys.back();
            keys.pop_back();
            cache.erase(lru_key);
            iterators.erase(lru_key);
            return lru_key;
        }

        bool contains(int item) const {
            return cache.find(item) != cache.end();
        }

        void print() const {
            cout << "LRU Cache:\n";
            for (const int key : keys) {
                cout << "" << key << " ";
            }
            cout << endl;
        }

};

int main() {
    LRU cache;

    cache.access(10); cache.access(20); cache.access(30);
    cout << "Cache after 10,20,30: "; cache.print(); // Expected: 30 20 10

    cache.access(20); // move 20 to front
    cout << "After accessing 20: "; cache.print(); // Expected: 20 30 10

    cout << "Remove LRU = " << cache.remove() << endl;

    cout << "Cache after remove: "; cache.print(); // Expected: 20 30

    cout << "Contains 10? " << (cache.contains(10) == 0 ? "false" : "true") << "\n"; // Expected: 0 (false)

    cout << "Size = " << cache.size() << "\n"; // Expected: Size = 2

    cout << "Empty = " << (cache.empty() == 0 ? "false" : "true") << "\n"; // Expected: Empty = 0 (false)

    return 0;
}