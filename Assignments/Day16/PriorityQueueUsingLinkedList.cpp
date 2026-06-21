/*Implement a priority queue where

Higher priority elements are dequeued first

Maintain sorted insertion
*/

#include <iostream>
using namespace std;

struct Element {
    int value;
    int priority;
};

class PriorityQueue {
private:
    Element arr[100];
    int size;

public:
    PriorityQueue() {
        size = 0;
    }

    // Insert while keeping the array sorted by priority
    void enqueue(int val, int prio) {
        if (size >= 100) {
            cout << "Queue Overflow!" << endl;
            return;
        }

        int i;
        // Start from the back and shift elements to the right 
        // until we find the correct spot for the new priority
        for (i = size - 1; i >= 0; i--) {
            if (arr[i].priority < prio) {
                arr[i + 1] = arr[i];
            } else {
                break;
            }
        }

        // Insert the new element at the found position
        arr[i + 1].value = val;
        arr[i + 1].priority = prio;
        size++;
        
        cout << "Inserted: " << val << " (Priority: " << prio << ")" << endl;
    }

    // Since it's sorted, the highest priority is always at index 0
    void dequeue() {
        if (size == 0) {
            cout << "Queue Underflow!" << endl;
            return;
        }

        cout << "Dequeued: " << arr[0].value << " with priority " << arr[0].priority << endl;

        // Shift all remaining elements left to fill the gap
        for (int i = 0; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    void display() {
        if (size == 0) return;
        cout << "Current Queue: ";
        for (int i = 0; i < size; i++) {
            cout << "[" << arr[i].value << ", P:" << arr[i].priority << "] ";
        }
        cout << endl;
    }
};

int main() {
    PriorityQueue pq;

    pq.enqueue(10, 2);
    pq.enqueue(30, 5); // Higher priority than 10
    pq.enqueue(20, 1); // Lower priority than 10
    pq.display();

    pq.dequeue(); // Should remove 30 first
    pq.display();

    return 0;
}