/* Merge two sorted linked lists into one sorted list */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* mergeSortedLists(Node* l1, Node* l2) {
    // 1. Create a dummy node to act as the starting point
    Node dummy(0);
    Node* tail = &dummy;

    // 2. Traverse both lists until one runs out
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // 3. Attach the remaining nodes of whichever list isn't empty
    if (l1 != nullptr) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    // Return the head of the merged list (the node after dummy)
    return dummy.next;
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
    // List 1: 1 -> 3 -> 5
    Node* l1 = new Node(1);
    l1->next = new Node(3);
    l1->next->next = new Node(5);

    // List 2: 2 -> 4 -> 6
    Node* l2 = new Node(2);
    l2->next = new Node(4);
    l2->next->next = new Node(6);

    cout << "List 1: "; printList(l1);
    cout << "List 2: "; printList(l2);

    Node* mergedHead = mergeSortedLists(l1, l2);

    cout << "Merged List: ";
    printList(mergedHead);

    return 0;
}