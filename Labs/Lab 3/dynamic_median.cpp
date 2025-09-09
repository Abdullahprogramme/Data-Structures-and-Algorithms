#include "maxpq_ra.hpp"
#include <queue>
#include <vector>
#include <stdexcept>

using namespace std;

class DynamicMedian {
    private:
        MaxPQ<int> maxHeap; // for keys < median
        MaxPQ<int> minHeap; // for keys > median
        int medianKey;
        bool hasMedian;

        void rebalance() {
            // Ensure size(maxHeap) == size(minHeap) or size(maxHeap) == size(minHeap) + 1
            while (maxHeap.size() > minHeap.size() + 1) {
                minHeap.insert(-medianKey);
                medianKey = maxHeap.delMax();
            }

            while (minHeap.size() > maxHeap.size()) {
                maxHeap.insert(medianKey);
                medianKey = -minHeap.delMax();
            }
        }

    public:
        DynamicMedian() : hasMedian(false) {}

        void insert(int key) {
            if (!hasMedian) {
                medianKey = key;
                hasMedian = true;
                return;
            }

            if (key < medianKey) {
                maxHeap.insert(key);
            } else {
                minHeap.insert(-key);
            }

            rebalance();
        }

        int median() const {
            if (!hasMedian) throw runtime_error("No keys present");

            return medianKey;
        }

        int removeMedian() {
            if (!hasMedian) throw runtime_error("No keys present");

            int result = medianKey;
            if (maxHeap.size() == 0 && minHeap.size() == 0) {
                hasMedian = false;
                return result;
            }

            if (maxHeap.size() >= minHeap.size()) {
                medianKey = maxHeap.delMax();
            } else {
                medianKey = -minHeap.delMax();
            }
            
            return result;
        }
};

int main() {
    DynamicMedian dm;
    dm.insert(5);
    dm.insert(3);
    dm.insert(8);
    dm.insert(1);
    dm.insert(4);

    cout << "Current Median: " << dm.median() << endl; // Should print 4

    cout << "Removed Median: " << dm.removeMedian() << endl; // Should print 4
    cout << "New Median: " << dm.median() << endl; // Should print 3

    return 0;
}