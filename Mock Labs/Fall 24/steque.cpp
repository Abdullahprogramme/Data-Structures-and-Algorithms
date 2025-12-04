#include <iostream>
#include <stdexcept>

using namespace std;

// Circular-array based Steque (stack-ended queue)
// Supports push (to top), pop (from top), enqueue (to end) in amortized O(1).
template <class Item>
class Steque {
    private:
        Item *a;        // underlying array
        int cap;        // capacity of array
        int head;       // index of top element
        int tail;       // index one past last element
        int n;          // number of elements

        void resize(int newCap) {
            Item *b = new Item[newCap];
            for (int i = 0; i < n; ++i) {
                b[i] = a[(head + i) % cap];
            }

            delete[] a;
            a = b;
            cap = newCap;
            head = 0;
            tail = n % cap;
        }

    public:
        Steque(int initial = 8) : a(nullptr), cap(0), head(0), tail(0), n(0) {
            if (initial < 1) initial = 8;

            cap = initial;
            a = new Item[cap];
            head = 0;
            tail = 0;
            n = 0;
        }

        ~Steque() {
            delete[] a;
        }

        // Adds an item to the top of the steque
        void push(const Item &item) {
            if (n == cap) resize(cap * 2);
            // move head back one position and write
            head = (head - 1 + cap) % cap;
            a[head] = item;
            ++n;
        }

        // Removes and returns the item from the top of the steque
        Item pop() {
            if (isEmpty()) throw runtime_error("pop from empty steque");

            Item item = a[head];
            head = (head + 1) % cap;
            --n;

            if (n > 0 && n <= cap / 4 && cap > 8) resize(cap / 2);
            return item;
        }

        // Adds an item to the end of the steque
        void enqueue(const Item &item) {
            if (n == cap) resize(cap * 2);

            a[tail] = item;
            tail = (tail + 1) % cap;
            ++n;
        }

        // Returns true if empty
        bool isEmpty() const { 
            return n == 0; 
        }

        // Number of items
        int size() const { 
            return n;
        }

        // Prints items from top to bottom
        void printSteque(ostream &os = cout) const {
            for (int i = 0; i < n; ++i) {
                if (i) os << ' ';
                os << a[(head + i) % cap];
            }
            os << '\n';
        }
};

// Simple demonstration / smoke test
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Steque<int> s;
    cout << "Steque demo (top -> bottom):\n";

    // push 1,2,3 -> top is 3
    s.push(1);
    s.push(2);
    s.push(3);
    cout << "After pushes: "; s.printSteque(); // should print 3 2 1

    // enqueue 4,5 -> go to bottom
    s.enqueue(4);
    s.enqueue(5);
    cout << "After enqueues: "; s.printSteque(); // 3 2 1 4 5

    // pop top
    int x = s.pop();
    cout << "popped: " << x << '\n';
    cout << "Now: "; s.printSteque(); // 2 1 4 5

    // mix operations
    s.enqueue(6);
    s.push(7);
    cout << "Mix: "; s.printSteque(); // 7 2 1 4 5 6

    // drain
    while (!s.isEmpty()) {
        cout << "pop: " << s.pop() << '\n';
    }

    cout << "Empty: " << boolalpha << s.isEmpty() << " size=" << s.size() << '\n';
    return 0;
}
