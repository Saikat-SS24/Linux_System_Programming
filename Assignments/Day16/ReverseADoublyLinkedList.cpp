/* Reverse a doubly linked list by modifying links */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

Node* reverseDLL(Node* head) {
    // If list is empty or has only one node
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node* curr = head;
    Node* temp = nullptr;

    // Traverse and swap next and prev pointers
    while (curr != nullptr) {
        // Swap logic
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        // Move to the next node in the original list
        // (Since we swapped, the 'original next' is now in curr->prev)
        head = curr; // Keep track of the last processed node
        curr = curr->prev;
    }

    return head; // New head of the reversed list
}

// Helper to print DLL
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = new Node(10);
    Node* n2 = new Node(20);
    Node* n3 = new Node(30);

    head->next = n2;
    n2->prev = head;
    n2->next = n3;
    n3->prev = n2;

    cout << "Original DLL: ";
    printList(head);

    head = reverseDLL(head);

    cout << "Reversed DLL: ";
    printList(head);

    return 0;
}