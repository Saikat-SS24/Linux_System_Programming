/* Find the middle node using slow and fast pointers */

#include <iostream>
using namespace std;

// Structure for a Node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Function to find the middle node
Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    // Fast moves 2 steps, slow moves 1 step
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // When fast reaches the end, slow is at the middle
    return slow;
}

// Helper to print list starting from a specific node
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    // Creating list: 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    cout << "Original List: ";
    printList(head);

    Node* middle = findMiddle(head);

    if (middle != nullptr) {
        cout << "The middle node is: " << middle->data << endl;
    }

    return 0;
}