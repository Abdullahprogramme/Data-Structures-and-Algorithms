#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Set {
    private:
        vector<T> elements;

        void resize(int newSize) {
            elements.resize(newSize);
        }

    public:
        void add(const T& key) {
            int i = 0;

            // Loop to find the existing element or the position to insert
            for (; i < elements.size(); ++i) {
                if (elements[i] == key) {
                    return; // Element already exists
                }

                if (elements[i] > key) {
                    break; // Found the position to insert
                }
            }

            // Resize
            resize(elements.size() + 1);

            // Shift elements to the right
            for (int j = elements.size() - 1; j > i; --j) {
                elements[j] = elements[j - 1];
            }

            // Insert the new element
            elements[i] = key;
        }

        bool contains(const T& key) const {
            int low = 0;
            int high = elements.size() - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (elements[mid] == key) {
                    return true; // Element found
                } else if (elements[mid] < key) {
                    low = mid + 1; 
                } else {
                    high = mid - 1;
                }
            }

            return false; // Element not found
        }

        T ceiling(const T& key) const {
            int low = 0;
            int high = elements.size() - 1;
            T ceilingValue;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (elements[mid] == key) {
                    return elements[mid]; // Exact match found
                } else if (elements[mid] < key) {
                    low = mid + 1; 
                } else {
                    ceilingValue = elements[mid];
                    high = mid - 1;
                }
            }

            return ceilingValue; // Return the smallest element >= key
        }

        int rank(const T& key) const {
            int low = 0;
            int high = elements.size() - 1;
            int numKeys = 0;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (elements[mid] == key) {
                    return mid; // Exact match found, return its index (number of keys < key)
                } else if (elements[mid] < key) {
                    numKeys = mid + 1;
                    low = mid + 1; 
                } else {
                    high = mid - 1;
                }
            }

            return numKeys; // Return the number of keys < key
        }

        T select(int i) const {
            if (i < 0 || i >= elements.size()) {
                throw out_of_range("Index out of range");
            }

            return elements[i];
        }

        T min() const {
            if (elements.empty()) {
                throw out_of_range("Set is empty");
            }

            return elements[0];
        }

        T remove(const T& key) {
            int i = 0;
            T removedElement;

            // Loop to find the existing element
            for (int j = 0; j < elements.size(); ++j) {
                if (elements[j] == key) {
                    removedElement = elements[j];
                    i = j;
                    break; // Element found
                }
            }

            for (int j = i; j < elements.size() - 1; ++j) {
                elements[j] = elements[j + 1];
            }

            resize(elements.size() - 1);
            return removedElement;
        }

        int size() const {
            return elements.size();
        }
};

// int main() {
//     Set<int> mySet;

//     mySet.add(5);
//     mySet.add(3);
//     mySet.add(8);
//     mySet.add(1);

//     // Set becomes {1, 3, 5, 8}

//     cout << "Contains 3: " << (mySet.contains(3) ? "true" : "false") << endl;
//     cout << "Contains 7: " << (mySet.contains(7) ? "true" : "false") << endl;

//     cout << "Ceiling of 4: " << mySet.ceiling(4) << endl;
//     cout << "Rank of 5: " << mySet.rank(5) << endl;

//     cout << "Select index 2: " << mySet.select(2) << endl;
//     cout << "Minimum element: " << mySet.min() << endl;

//     cout << "Removing 3: " << mySet.remove(3) << endl;
//     cout << "Contains 3 after removal: " << (mySet.contains(3) ? "true" : "false") << endl;

//     return 0;
// }