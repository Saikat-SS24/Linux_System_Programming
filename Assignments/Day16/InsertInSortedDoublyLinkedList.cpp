/* Insert in Sorted Doubly Linked List
Insert a node while maintaining sorted order */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next, *prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

Node* sortedInsert(Node* head, int val) {
    Node* newNode = new Node(val);

    // Case 1: List is empty
    if (head == nullptr) {
        return newNode;
    }

    // Case 2: Insert before the head (new node becomes new head)
    if (val < head->data) {
        newNode->next = head;
        head->prev = newNode;
        return newNode;
    }

    // Case 3: Traverse to find the insertion point
    Node* curr = head;
    while (curr->next != nullptr && curr->next->data < val) {
        curr = curr->next;
    }

    // Insert newNode after curr
    newNode->next = curr->next;
    newNode->prev = curr;

    // If we are not inserting at the very end
    if (curr->next != nullptr) {
        curr->next->prev = newNode;
    }
    
    curr->next = newNode;

    return head;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = nullptr;

    head = sortedInsert(head, 30);
    head = sortedInsert(head, 10);
    head = sortedInsert(head, 20);
    head = sortedInsert(head, 40);

    cout << "Sorted DLL: ";
    printList(head);

    return 0;
}