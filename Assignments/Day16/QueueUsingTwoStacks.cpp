/*Implement queue operations (enqueue, dequeue) using two stacks
*/

#include <iostream>
#include <stack>
using namespace std;

class QueueUsingStacks {
    stack<int> s1, s2;

public:
    // Enqueue: Simply push to the first stack
    void enqueue(int x) {
        s1.push(x);
        cout << "Enqueued: " << x << endl;
    }

    // Dequeue: Pop from the second stack
    int dequeue() {
        // If both stacks are empty, queue is empty
        if (s1.empty() && s2.empty()) {
            cout << "Queue Underflow!" << endl;
            return -1;
        }

        // If s2 is empty, move all elements from s1 to s2
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        // Now the top of s2 is the oldest element (FIFO)
        int topVal = s2.top();
        s2.pop();
        return topVal;
    }
};

int main() {
    QueueUsingStacks q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Dequeued: " << q.dequeue() << endl; // Should be 10
    cout << "Dequeued: " << q.dequeue() << endl; // Should be 20

    q.enqueue(40);
    cout << "Dequeued: " << q.dequeue() << endl; // Should be 30
    cout << "Dequeued: " << q.dequeue() << endl; // Should be 40

    return 0;
}