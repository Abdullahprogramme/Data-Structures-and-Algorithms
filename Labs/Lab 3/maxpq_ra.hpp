#pragma once
#include <random>
#include <iostream>
#include <utility>

using namespace std;

template<typename Key> 
class MaxPQ {
    private: 
        int capacity; // Current capacity of the array
        int n; // Number of elements in the priority queue
        Key* pq; // Array to store the heap elements
 
        // Resize the underlying array to the new capacity
        void resize(int newCapacity) {
            Key* newPq = new Key[newCapacity + 1];
            for(int i = 1; i <= n; i++) {
                newPq[i] = move(pq[i]);
            }

            delete[] pq;
            pq = newPq;
            capacity = newCapacity;
        }
        
        // Restore the heap order by swimming up the element at index k
        void swim(int k) {
            while (k > 1 && pq[k/2] < pq[k]) {
                swap(pq[k], pq[k/2]);
                k = k/2;
            }
        }

        // Restore the heap order by sinking down the element at index k
        void sink(int k) {
            while (2*k <= n) {
                int j = 2*k;
                if (j < n && pq[j] < pq[j+1])
                    j++;

                if (!(pq[k] < pq[j])) break;
                swap(pq[k], pq[j]);
                k = j;
            }
        }

    public: 
        // Constructor
        MaxPQ() : capacity(2), n(0)    {  
            pq = new Key[capacity+1];  
        }
        
        // Destructor
        ~MaxPQ() {  
            delete[] pq;  
        }

        // Check if the priority queue is empty
        bool empty() {   
            return n == 0;   
        }

        // Get the number of elements in the priority queue
        int size()  {   
            return n;        
        }

        // Insert a new element into the priority queue
        void insert(Key x) {
            // Add overflow check and resizing logic
            if (n == capacity) 
               resize(2 * capacity);

            // Insert new element at the end of the heap
            // and then swim it to restore heap order
            pq[++n] = x;
            swim(n);
        }

        // Delete and return the maximum element from the priority queue
        Key delMax() {
            // Add underflow check and resizing logic
            if (n == 0) 
               throw runtime_error("Priority queue underflow");
            else if (n == capacity / 4) 
               resize(capacity / 2);

            // Exchange the root of the heap with the last element
            // and then sink the new root to restore heap order
            swap(pq[1], pq[n--]);
            sink(1);
            
            return move(pq[n+1]);
        } 

        // Delete and return a random element from the priority queue
        Key deleteRandom() {
            if (n == 0) 
               throw runtime_error("Priority queue underflow");
            else if (n == capacity / 4) 
               resize(capacity / 2);

            // Generate a random index between 1 and n
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, n);
            int randomIndex = dis(gen);

            // Exchange the randomly selected element with the last element
            // and then sink the new element at randomIndex to restore heap order
            swap(pq[randomIndex], pq[n--]);
            sink(randomIndex);

            return move(pq[n+1]);
        }
};
