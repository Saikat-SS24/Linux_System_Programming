/* Detect a loop using Floyd's Cycle Detection and remove it */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void removeLoop(Node* loopNode, Node* head) {
    Node* ptr1 = head;
    Node* ptr2 = loopNode;

    // Find the number of nodes in the loop or find the starting point
    // Move both at the same speed. They will meet at the start of the loop.
    // Special case: if they meet at the head
    if (ptr1 == ptr2) {
        while (ptr2->next != ptr1) {
            ptr2 = ptr2->next;
        }
    } else {
        while (ptr1->next != ptr2->next) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    // Set the next of the last node to NULL to break the loop
    ptr2->next = nullptr;
}

bool detectAndRemoveLoop(Node* head) {
    Node *slow = head, *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        // Loop detected
        if (slow == fast) {
            removeLoop(slow, head);
            return true;
        }
    }
    return false; // No loop found
}

// Helper to print list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    // Create a loop for testing: 5 points back to 3
    head->next->next->next->next->next = head->next->next;

    if (detectAndRemoveLoop(head)) {
        cout << "Loop detected and removed!" << endl;
    } else {
        cout << "No loop detected." << endl;
    }

    printList(head);
    return 0;
}