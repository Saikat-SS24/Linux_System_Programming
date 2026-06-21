/*Implement a circular queue using array:

detect overflow and underflow

support wrap - around
*/

#include <iostream>
using namespace std;

class CircularQueue {
private:
    int *arr;
    int front, rear, size;

public:
    CircularQueue(int n) {
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    // Check if queue is full (Overflow)
    bool isFull() {
        return (front == (rear + 1) % size);
    }

    // Check if queue is empty (Underflow)
    bool isEmpty() {
        return (front == -1);
    }

    // Add an element (Enqueue)
    void enqueue(int value) {
        if (isFull()) {
            cout << "Overflow! Queue is full.\n";
            return;
        }
        
        // If it's the first element being added
        if (isEmpty()) {
            front = 0;
        }

        // Wrap around logic for rear
        rear = (rear + 1) % size;
        arr[rear] = value;
        cout << value << " added to queue.\n";
    }

    // Remove an element (Dequeue)
    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow! Queue is empty.\n";
            return;
        }

        cout << arr[front] << " removed from queue.\n";

        // If the queue has only one element, reset pointers
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            // Wrap around logic for front
            front = (front + 1) % size;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % size;
        }
        cout << endl;
    }
};

int main() {
    int s;
    cout << "Enter size of circular queue: ";
    cin >> s;

    CircularQueue q(s);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();

    q.dequeue();
    q.enqueue(40); // This will wrap around if size was 3
    q.display();

    return 0;
}