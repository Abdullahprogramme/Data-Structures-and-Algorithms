// Symbol Table Implementation in C++ with operator[] Overload
#include <iostream>
#include <stdexcept>
#include <map>

using namespace std;

template<typename Key, typename Value>
class SymbolTable {
    private:
        map<Key, Value> table;

        bool isEmpty() const {
            return table.empty();
        }

        bool contains(const Key& key) const {
            return table.find(key) != table.end();
        }

    public:
        SymbolTable() = default;
        ~SymbolTable() = default;

        // Overload operator[] for insertion and access
        Value& operator[](const Key& key) {
            if (key == Key()) {
                throw invalid_argument("Key cannot be null");
            }

            return table[key];
        }

        // Const version for read-only access
        const Value& operator[](const Key& key) const {
            if (key == Key()) {
                throw invalid_argument("Key cannot be null");
            }

            auto it = table.find(key);
            if (it == table.end()) {
                throw out_of_range("Key does not exist");
            }
            return it->second;
        }

        void deleteKey(const Key& key) {
            if (key == Key()) {
                throw invalid_argument("Key cannot be null");
            }

            if (!contains(key)) {
                throw invalid_argument("Key does not exist");
            }

            table.erase(key);
        }

        int size() const {
            return table.size();
        }

        const map<Key, Value>& getTable() const {
            return table;
        }

        int maxFrequency() const {
            int maxFreq = 0;
            for (const auto& pair : table) {
                if (pair.second > maxFreq) {
                    maxFreq = pair.second;
                }
            }
            return maxFreq;
        }
        
        int minFrequency() const {
            if (isEmpty()) {
                throw runtime_error("Symbol table is empty");
            }

            int minFreq = table.begin()->second;
            for (const auto& pair : table) {
                if (pair.second < minFreq) {
                    minFreq = pair.second;
                }
            }
            
            return minFreq;
        }
};

// Non-member operator<< overload for SymbolTable
template<typename Key, typename Value>
ostream& operator<<(ostream& os, const SymbolTable<Key, Value>& st) {
    for (const auto& pair : st.getTable()) {
        os << pair.first << " : " << pair.second << "\n";
    }
    return os;
}

int main() {
    SymbolTable<string, int> st;

    st["Alice"] = 30;
    st["Bob"] = 25;
    st["Charlie"] = 35;
    st["Charlie"]++;

    cout << "Symbol Table:\n" << st;

    cout << "Size: " << st.size() << "\n";

    cout << "Get Alice's age: " << st["Alice"] << "\n";

    st.deleteKey("Bob");
    cout << "After deleting Bob:\n" << st;

    cout << "Max Frequency: " << st.maxFrequency() << "\n";
    cout << "Min Frequency: " << st.minFrequency() << "\n";

    return 0;
}
