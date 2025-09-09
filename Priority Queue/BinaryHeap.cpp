// Priority Queue using Binary Heap

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

template <typename T>
class PriorityQueue {
    private:
        vector<T> heap;
        int n;
        bool isMinHeap;

        bool empty() const {
            return n == 0;
        }

        int size() const {
            return n;
        }

        void heapifyUp(int index) {
            if (index && ((isMinHeap && heap[parent(index)] > heap[index]) || (!isMinHeap && heap[parent(index)] < heap[index]))) {
                swap(heap[index], heap[parent(index)]);
                heapifyUp(parent(index));
            }
        }

        void heapifyDown(int index) {
            int left = leftChild(index);
            int right = rightChild(index);
            int extremum = index;

            if (left < n && ((isMinHeap && heap[left] < heap[extremum]) || (!isMinHeap && heap[left] > heap[extremum]))) {
                extremum = left;
            }

            if (right < n && ((isMinHeap && heap[right] < heap[extremum]) || (!isMinHeap && heap[right] > heap[extremum]))) {
                extremum = right;
            }

            if (extremum != index) {
                swap(heap[index], heap[extremum]);
                heapifyDown(extremum);
            }
        }

        int parent(int index) const {
            return (index - 1) / 2;
        }

        int leftChild(int index) const {
            return 2 * index + 1;
        }

        int rightChild(int index) const {
            return 2 * index + 2;
        }

    public:
        PriorityQueue(bool minHeap = true, int N = 3) : n(0), isMinHeap(minHeap) {
            heap.resize(N);
        }

        void push(const T& value) {
            if (n == heap.size()) {
                // Resize the heap if it's full
                heap.resize(heap.size() * 2);
            }

            heap[n] = value;
            n++;
            heapifyUp(n - 1);
        }

        T pop() {
            if (empty()) {
                throw runtime_error("Priority Queue is empty");
            }

            T root = heap[0];
            heap[0] = heap[--n];
            heapifyDown(0);
            return root;
        }

        T top() const {
            if (empty()) {
                throw runtime_error("Priority Queue is empty");
            }

            return heap[0];
        }

        void operator<<(ostream& os) const {
            for (int i = 0; i < n; ++i) {
                os << heap[i] << " ";
            }
            os << endl;
        }
};

// Example usage
int main() {
    PriorityQueue<int> minHeap(true);
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(20);
    minHeap.push(1);
    cout << "Min-Heap Top: " << minHeap.top() << endl; // Should print 5
    minHeap.pop();
    cout << "Min-Heap Top after pop: " << minHeap.top() << endl; // Should print 10

    PriorityQueue<int> maxHeap(false);
    maxHeap.push(10);
    maxHeap.push(5);
    maxHeap.push(20);
    maxHeap.push(1);
    cout << "Max-Heap Top: " << maxHeap.top() << endl; // Should print 20
    maxHeap.pop();
    cout << "Max-Heap Top after pop: " << maxHeap.top() << endl; // Should print 10

    return 0;
}