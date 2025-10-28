#pragma once

#include <string>
#include <vector>
#include <list>

using namespace std;

// Separate chaining hash table
class HashTable {
    private:
        struct Entry {
            string key;
            bool isWord;   // true if an actual full dictionary word
            bool isPrefix; // true if this entry represents a prefix of some word
        };

        vector<list<Entry>> table;
        size_t tableSize;
        size_t numElements;
        size_t maxWordLen;

        size_t hash(const string &s) const;
        static bool isPrime(size_t n);
        static size_t nextPrime(size_t n);

    public:

        // construct with approximate capacity (will be rounded to a prime)
        HashTable(size_t approxCapacity = 101);
        ~HashTable();

        void insertWord(const string &w); // insert the word
        
        void insertPrefix(const string &p); // insert a prefix
        
        bool containsWord(const string &w) const; // check if exact word exists

        bool containsPrefix(const string &prefix) const; // check if prefix exists (i.e., any word in table starts with this prefix)

        // set the maximum word length expected
        void setMaxWordLength(size_t m) { 
            maxWordLen = m; 
        }

        // return the maximum word length expected
        size_t getMaxWordLength() const { 
            return maxWordLen; 
        }
};