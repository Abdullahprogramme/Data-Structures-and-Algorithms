// Queue using two stacks

#include <iostream>
#include <stack>
#include <stdexcept>

using namespace std;

class QueueUsingStacks {
    private:
        stack<int> stack1;
        stack<int> stack2;

        void transferStack1ToStack2() {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }

    public:
        void enqueue(int value) {
            stack1.push(value);
        }

        int dequeue() {
            if (stack2.empty()) {
                if (stack1.empty()) {
                    throw runtime_error("Queue is empty");
                }
                
                transferStack1ToStack2();
            }

            int frontValue = stack2.top();
            stack2.pop();

            return frontValue;
        }

        int front() {
            if (stack2.empty()) {
                if (stack1.empty()) {
                    throw runtime_error("Queue is empty");
                }
                
                transferStack1ToStack2();
            }

            return stack2.top();
        }

        bool isEmpty() const {
            return stack1.empty() && stack2.empty();
        }

        int size() const {
            return stack1.size() + stack2.size();
        }
};

int main() {
    QueueUsingStacks q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "Front: " << q.front() << endl; // Output: 1
    cout << "Dequeue: " << q.dequeue() << endl; // Output: 1

    q.enqueue(4);
    q.enqueue(5);

    cout << "Size: " << q.size() << endl; // Output: 4
    cout << "Dequeue: " << q.dequeue() << endl; // Output: 2
    cout << "Dequeue: " << q.dequeue() << endl; // Output: 3
    cout << "Front: " << q.front() << endl; // Output: 4
    
    return 0;
}