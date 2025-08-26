#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include "stopwatch.hpp"

using namespace std;

// =============================
// Part A: Resizable Array
// =============================
class ResizableArray {
    private:
        int* data;
        int capacity;
        int size;

        void resize(int newCapacity) {
            int* newData = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

    public:
        ResizableArray() {
            data = new int[1];
            capacity = 1;
            size = 0;
        }

        ~ResizableArray() {
            delete[] data;
        }

        void push_back(int value) {
            if (size == capacity) {
                resize(capacity * 2);
            }
            data[size] = value;
            size++;
        }

        void pop_back() {
            if (empty()) {
                throw out_of_range("Array is empty");
            }
            size--;
        }

        int get(int index) const {
            if (index < 0 || index >= size) {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }

        int getSize() const {
            return size;
        }

        bool empty() const {
            if (size == 0) {
                return true;
            }
            return false;
        }
};

// =============================
// Part B: Linked List
// =============================
class LinkedList {
    private:
        struct Node {
            int data;
            Node* next;
            Node(int val) : data(val), next(nullptr) {}
        };

        Node* head;
        Node* tail;
        int size;

    public:
        LinkedList() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        ~LinkedList() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        void insertAtHead(int value) {
            if (head == nullptr) {
                head = new Node(value);
                tail = head;
            } else {
                Node* newNode = new Node(value);
                newNode->next = head;
                head = newNode;
            }
            size++;
        }

        void insertAtTail(int value) {
            if (tail == nullptr) {
                head = new Node(value);
                tail = head;
            } else {
                Node* newNode = new Node(value);
                tail->next = newNode;
                tail = newNode;
            }
            size++;
        }

        void deleteHead() {
            if (empty()) {
                throw out_of_range("List is empty");
            }
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            if (head == nullptr) {
                tail = nullptr;
            }
        }

        int get(int i) const {
            if (i < 0 || i >= size) {
                throw out_of_range("Index out of range");
            }
            Node* current = head;
            for (int j = 0; j < i; j++) {
                current = current->next;
            }
            return current->data;
        }

        bool empty() const {
            return size == 0;
        }

        int getSize() const {
            return size;
        }
};

// =============================
// Part C: Stack Implementations
// =============================

// --- Stack using ResizableArray ---
class ArrayStack {
    private:
        ResizableArray arr;

    public:
        ArrayStack() = default;

        // Copy constructor for deep copy
        ArrayStack(const ArrayStack& other) {
            for (int i = 0; i < other.arr.getSize(); ++i) {
                arr.push_back(other.arr.get(i));
            }
        }

        void push(int value) {
            arr.push_back(value);
        }

        void pop() {
            arr.pop_back();
        }

        int top() const {
            return arr.get(arr.getSize() - 1);
        }

        bool empty() const {
            return arr.empty();
        }
};

// --- Stack using LinkedList ---
class LinkedListStack {
    private:
        LinkedList list;

    public:
        LinkedListStack() = default;

        // Copy constructor for deep copy
        LinkedListStack(const LinkedListStack& other) {
            for (int i = 0; i < other.list.getSize(); ++i) {
                list.insertAtTail(other.list.get(i));
            }
        }

        void push(int value) {
            list.insertAtHead(value);
        }

        void pop() {
            list.deleteHead();
        }

        int top() const {
            return list.get(0);
        }
        
        bool empty() const {
            return list.empty();
        }
};

// =============================
// Part D: Text Buffer
// =============================

// --- TextBuffer using ArrayStack ---
class TextBufferArray {
    private:
        ArrayStack left;   // characters to the left of cursor
        ArrayStack right;  // characters to the right of cursor

    public:
        void insert(char c) {
            left.push(c);
        }

        void remove() {
            if (!left.empty()) {
                left.pop();
            }
        }

        void moveLeft() {
            if (!left.empty()) {
                right.push(left.top());
                left.pop();
            }
        }

        void moveRight() {
            if (!right.empty()) {
                left.push(right.top());
                right.pop();
            }
        }

        string getText() {
            string text;

            // Temporary stack for reversing left stack
            ArrayStack tempLeft = left;
            ArrayStack tempRight = right;

            // Get text from left stack
            while (!tempLeft.empty()) {
                text.push_back(tempLeft.top());
                tempLeft.pop();
            }

            // Reverse the text from left stack
            reverse(text.begin(), text.end());

            // Get text from right stack
            while (!tempRight.empty()) {
                text.push_back(tempRight.top());
                tempRight.pop();
            }
            return text;
        }
};

// --- TextBuffer using LinkedListStack ---
class TextBufferList {
    private:
        LinkedListStack left;
        LinkedListStack right;

    public:
        void insert(char c) {
            left.push(c);
        }

        void remove() {
            left.pop();
        }

        void moveLeft() {
            if (!left.empty()) {
                right.push(left.top());
                left.pop();
            }
        }

        void moveRight() {
            if (!right.empty()) {
                left.push(right.top());
                right.pop();
            }
        }

        string getText() {
            string text;

            // Temporary stack for reversing left stack
            LinkedListStack tempLeft = left;
            LinkedListStack tempRight = right;

            // Get text from left stack
            while (!tempLeft.empty()) {
                text.push_back(tempLeft.top());
                tempLeft.pop();
            }

            // Reverse the text from left stack
            reverse(text.begin(), text.end());

            // Get text from right stack
            while (!tempRight.empty()) {
                text.push_back(tempRight.top());
                tempRight.pop();
            }
            return text;
        }
};

// =============================
// Driver Program
// =============================
int main() {
    cout << "Testing TextBuffer with ArrayStack...\n";
    TextBufferArray buf1;
    string text = "datastructures";

    // Initialize stopwatch
    Stopwatch stopwatch;
    for (char c : text) buf1.insert(c);

    buf1.moveLeft(); buf1.moveLeft(); buf1.moveLeft(); buf1.moveLeft(); buf1.moveLeft();
    buf1.insert('X');
    cout << "After inserting X: " << buf1.getText() << endl;

    buf1.remove();
    buf1.remove();
    buf1.remove();
    cout << "After deleting 3 chars: " << buf1.getText() << endl;

    buf1.moveRight();
    buf1.moveRight();
    buf1.insert('Y');
    cout << "After inserting Y: " << buf1.getText() << endl;

    // Measure elapsed time
    double elapsed = stopwatch.elapsedTime();
    cout << "Elapsed time: " << elapsed << " seconds" << endl;
    
    cout << "\nTesting TextBuffer with LinkedListStack...\n";
    TextBufferList buf2;
    stopwatch.reset();
    for (char c : text) buf2.insert(c);

    buf2.moveLeft(); buf2.moveLeft(); buf2.moveLeft(); buf2.moveLeft(); buf2.moveLeft();
    buf2.insert('X');
    cout << "After inserting X: " << buf2.getText() << endl;

    buf2.remove();
    buf2.remove();
    buf2.remove();
    cout << "After deleting 3 chars: " << buf2.getText() << endl;

    buf2.moveRight();
    buf2.moveRight();
    buf2.insert('Y');
    cout << "After inserting Y: " << buf2.getText() << endl;

    // Measure elapsed time
    elapsed = stopwatch.elapsedTime();
    cout << "Elapsed time: " << elapsed << " seconds" << endl;

    return 0;
}
