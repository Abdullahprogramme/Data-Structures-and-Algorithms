#include "hashTable.hpp"
#include <cmath>
#include <functional>

using namespace std;

static const size_t DEFAULT_PRIME = 101;

size_t HashTable::hash(const string &s) const {
    // polynomial rolling hash (mod tableSize)
    unsigned long long h = 0;
    const unsigned long long B = 127ULL;
    for (char ch : s) {
        h = h * B + static_cast<unsigned char>(ch);
    }
    return (size_t)(h % tableSize);
}

bool HashTable::isPrime(size_t n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (size_t i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

size_t HashTable::nextPrime(size_t n) {
    if (n <= 2) return 2;
    size_t p = (n % 2 == 0) ? n + 1 : n;
    while (!isPrime(p)) p += 2;
    return p;
}

HashTable::HashTable(size_t approxCapacity) {
    tableSize = nextPrime((approxCapacity > 3) ? approxCapacity : DEFAULT_PRIME);
    table.resize(tableSize);
    numElements = 0;
    maxWordLen = 0;
}

HashTable::~HashTable() {}

void HashTable::insertWord(const string &word) {
    size_t idx = hash(word);
    for (auto &e : table[idx]) {

        // if key already exists, update flags
        if (e.key == word) {
            e.isWord = true;
            e.isPrefix = true;
            return;
        }
    }

    Entry en; en.key = word; en.isWord = true; en.isPrefix = true;
    table[idx].push_front(en);
    numElements++;
}
    
void HashTable::insertPrefix(const string &prefix) {
    size_t idx = hash(prefix);
    for (auto &e : table[idx]) {
        if (e.key == prefix) {
            e.isPrefix = true;
            return;
        }
    }
    Entry en; en.key = prefix; en.isWord = false; en.isPrefix = true;
    table[idx].push_front(en);
    numElements++;
}

bool HashTable::containsWord(const string &word) const {
    size_t idx = hash(word);
    for (const auto &e : table[idx]) if (e.key == word && e.isWord) return true;
    return false;
}

bool HashTable::containsPrefix(const string &prefix) const {
    size_t idx = hash(prefix);
    for (const auto &e : table[idx]) if (e.key == prefix && e.isPrefix) return true;
    return false;
}