// Minstack 

#include <iostream>
#include <stack>
#include <stdexcept>

using namespace std;

class MinStack {
    private:
        stack<int> mainStack;
        stack<int> minStack;

    public:
        MinStack() {}

        void push(int x) {
            mainStack.push(x);
            if (minStack.empty() || x <= minStack.top()) {
                minStack.push(x);
            }
        }

        void pop() {
            if (mainStack.empty()) {
                throw runtime_error("Stack is empty");
            }

            if (mainStack.top() == minStack.top()) {
                minStack.pop();
            }

            mainStack.pop();
        }

        int top() {
            if (mainStack.empty()) {
                throw runtime_error("Stack is empty");
            }

            return mainStack.top();
        }

        int getMin() {
            if (minStack.empty()) {
                throw runtime_error("Stack is empty");
            }

            return minStack.top();
        }

        bool empty() {
            return mainStack.empty();
        }

        int size() {
            return mainStack.size();
        }
};

int main() {
    MinStack ms;

    ms.push(5);
    ms.push(2);
    ms.push(7);
    ms.push(1);

    cout << "Min: " << ms.getMin() << endl; // Output: 1
    cout << "Top: " << ms.top() << endl; // Output: 1

    ms.pop(); // Remove 1

    cout << "Min: " << ms.getMin() << endl; // Output: 2
    cout << "Top: " << ms.top() << endl; // Output: 7

    ms.pop(); // Remove 7
    ms.pop(); // Remove 2

    cout << "Min: " << ms.getMin() << endl; // Output: 5
    cout << "Size: " << ms.size() << endl; // Output: 1
    
    return 0;
}