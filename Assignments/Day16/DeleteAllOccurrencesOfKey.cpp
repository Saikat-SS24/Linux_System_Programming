/* Delete All Occurrences of Key
Delete all nodes with a given value from a doubly linked list */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next, *prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

Node* deleteAllOccurrences(Node* head, int key) {
    if (head == nullptr) return nullptr;

    Node* curr = head;
    Node* nextNode;

    while (curr != nullptr) {
        if (curr->data == key) {
            // Save next node before we delete the current one
            nextNode = curr->next;

            // Step 1: If the node to be deleted is the HEAD
            if (curr == head) {
                head = curr->next;
            }

            // Step 2: Update 'next' of the previous node
            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            }

            // Step 3: Update 'prev' of the next node
            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }

            delete curr; // Free memory
            curr = nextNode; // Move to saved next node
        } 
        else {
            curr = curr->next; // Move to next node normally
        }
    }
    return head;
}

// Helper to print DLL
void printList(Node* head) {
    if (!head) {
        cout << "List is empty" << endl;
        return;
    }
    while (head != nullptr) {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    // Creating: 10 <-> 20 <-> 10 <-> 30 <-> 10
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->prev = head;
    head->next->next = new Node(10);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(30);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new Node(10);
    head->next->next->next->next->prev = head->next->next->next;

    cout << "Before deleting 10: ";
    printList(head);

    head = deleteAllOccurrences(head, 10);

    cout << "After deleting 10:  ";
    printList(head);

    return 0;
}