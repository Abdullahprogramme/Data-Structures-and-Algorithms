// Priority Queue implementation using a vector (min-heap) and (max-heap)

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class PriorityQueue {
    private:
        vector<T> queue;
        int n;
        bool isMinHeap;

        bool empty() const {
            return n == 0;
        }

        int size() const {
            return n;
        }

    public:
        PriorityQueue(bool minHeap = true, int N = 10) : n(0), isMinHeap(minHeap) {
            queue.resize(N);
        }

        void push(const T& value) {
            if (n == queue.size()) {
                throw runtime_error("Priority Queue is full");
            }

            // Arranging the elements, if min-heap then smallest element at the top else largest element at the top
            for (int i = n - 1; i >= 0; --i) {
                if ((isMinHeap && queue[i] < value) || (!isMinHeap && queue[i] > value)) {
                    queue[i + 1] = queue[i];
                } else {
                    queue[i + 1] = value;
                    n++;
                    return;
                }
            }

            queue[0] = value;
            n++;
        }

        T pop() {
            if (empty()) {
                throw runtime_error("Priority Queue is empty");
            }

            // Always return the top element
            return queue[--n];
        }

        T top() const {
            if (empty()) {
                throw runtime_error("Priority Queue is empty");
            }

            return queue[n - 1];
        }

        void operator<<(ostream& os) const {
            for (int i = n - 1; i >= 0; --i) {
                os << queue[i] << " ";
            }
            os << endl;
        }
};

int main() {
    PriorityQueue<int> minHeap(true, 10); // Min-Heap
    minHeap.push(5);
    minHeap.push(1);
    minHeap.push(3);
    minHeap.push(4);
    minHeap.push(2);

    cout << "Min-Heap: ";
    minHeap << cout;

    cout << "Top element: " << minHeap.top() << endl; // Should be 1

    cout << "Popped element: " << minHeap.pop() << endl; // Should be 1
    cout << "After popping, new top element: " << minHeap.top() << endl; // Should be 2

    cout << "Min-Heap after popping: ";
    minHeap << cout;

    cout << endl << "---------------------" << endl << endl;

    PriorityQueue<int> maxHeap(false, 10); // Max-Heap
    maxHeap.push(5);
    maxHeap.push(1);
    maxHeap.push(3);
    maxHeap.push(4);
    maxHeap.push(2);

    cout << "Max-Heap: ";
    maxHeap << cout;

    cout << "Top element: " << maxHeap.top() << endl; // Should be 5

    cout << "Popped element: " << maxHeap.pop() << endl; // Should be 5
    cout << "After popping, new top element: " << maxHeap.top() << endl; // Should be 4

    cout << "Max-Heap after popping: ";
    maxHeap << cout;

    return 0;
}