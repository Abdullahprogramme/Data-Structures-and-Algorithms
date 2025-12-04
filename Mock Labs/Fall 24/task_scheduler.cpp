// Task Scheduler Implementation

#include <iostream>
#include <utility>
#include <string>

using namespace std;

struct Task {
    string description;
    int priority;

    Task(const string &desc = "", int prio = 0) : description(desc), priority(prio) { }

    bool operator<(const Task &other) const {
        return priority < other.priority;
    }

    bool operator>=(const Task &other) const {
        return priority >= other.priority;
    }
};

class TaskScheduler {
    private:
        int capacity;
        int n;
        Task* pq;

        void swim(int k) {
            while (k > 1 && pq[k/2] < pq[k]) {
                swap(pq[k], pq[k/2]);
                k = k/2;
            }
        }

        void sink(int k) {
            while (2*k <= n) {
                int j = 2*k;
                if (j < n && pq[j] < pq[j+1]) j++;

                if (pq[k] >= pq[j]) break;
                swap(pq[k], pq[j]);
                k = j;
            }
        }

    public:
        TaskScheduler(int cap = 16) : capacity(cap), n(0) {
            pq = new Task[capacity + 1];
        }

        ~TaskScheduler() {
            delete[] pq;
        }

        void AddTask(const Task &task) {
            if (n == capacity) {
                // Resize logic can be added here
                throw runtime_error("TaskScheduler capacity reached");
            }

            pq[++n] = task;
            swim(n);
        }

        Task RemoveHighestPriorityTask() {
            if (n == 0) throw runtime_error("No tasks to remove");

            Task maxTask = pq[1];
            swap(pq[1], pq[n--]);
            sink(1);
            pq[n+1] = Task(); // Optional: Reset the removed task slot

            return maxTask;
        }

        bool isQueueFull() {
            return n == capacity;
        }

        void ListAllTasks() {
            for (int i = 1; i <= n; ++i) {
                cout << "Task: " << pq[i].description << ", Priority: " << pq[i].priority << endl;
            }
        }
};

// Example usage
int main() {
    TaskScheduler scheduler;

    scheduler.AddTask(Task("Task 1", 5));
    scheduler.AddTask(Task("Task 2", 10));
    scheduler.AddTask(Task("Task 3", 3));

    cout << "All Tasks:" << endl;
    scheduler.ListAllTasks();

    Task highest = scheduler.RemoveHighestPriorityTask();
    cout << "Removed Highest Priority Task: " << highest.description << " with priority " << highest.priority << endl;

    cout << "Remaining Tasks:" << endl;
    scheduler.ListAllTasks();

    return 0;
}