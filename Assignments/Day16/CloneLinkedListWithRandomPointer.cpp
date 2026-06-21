/* Clone Linked List with Random Pointer
Each node has:
- next
- random pointer 
Clone the entire list */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next, *random;
    Node(int val) : data(val), next(nullptr), random(nullptr) {}
};

Node* cloneLinkedList(Node* head) {
    if (!head) return nullptr;

    // STEP 1: Create copy nodes and interweave
    Node* curr = head;
    while (curr) {
        Node* copy = new Node(curr->data);
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }

    // STEP 2: Assign random pointers for the copies
    curr = head;
    while (curr) {
        if (curr->random) {
            // The copy's random is the node after the original's random
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    // STEP 3: Separate the two lists
    Node* original = head;
    Node* copyHead = head->next;
    Node* tempCopy = copyHead;

    while (original) {
        original->next = original->next->next;
        if (tempCopy->next) {
            tempCopy->next = tempCopy->next->next;
        }
        
        original = original->next;
        tempCopy = tempCopy->next;
    }

    return copyHead;
}

void printList(Node* head) {
    while (head) {
        cout << "Data: " << head->data;
        if (head->random) cout << ", Random: " << head->random->data;
        else cout << ", Random: NULL";
        cout << endl;
        head = head->next;
    }
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->random = head->next; // 1's random is 2
    head->next->random = head; // 2's random is 1

    cout << "Original List:\n";
    printList(head);

    Node* cloned = cloneLinkedList(head);

    cout << "\nCloned List:\n";
    printList(cloned);

    return 0;
}