/* Reverse nodes in groups of size k
Example: 1->2->3->4->5, k = 2 -> 2->1->4->3->5 */

#include <iostream>
using namespace std;

// Define the Node structure
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* reverseKGroup(Node* head, int k) {
    // 1. Check if there are at least k nodes to reverse
    Node* check = head;
    for (int i = 0; i < k; i++) {
        if (!check) return head; // Fewer than k nodes, return head as is
        check = check->next;
    }

    // 2. Reverse the first k nodes
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    int count = 0;

    while (curr != nullptr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    // 3. After reversal, 'head' is the tail of the reversed group.
    // Connect it to the next reversed group recursively.
    if (next != nullptr) {
        head->next = reverseKGroup(next, k);
    }

    // 4. 'prev' is the new head of this reversed group
    return prev;
}

// Helper function to print the list
void printList(Node* node) {
    while (node) {
        cout << node->data << " -> ";
        node = node->next;
    }
    cout << "NULL" << endl;
}

int main() {
    // Create: 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    int k = 2;
    cout << "Original List: ";
    printList(head);

    head = reverseKGroup(head, k);

    cout << "Reversed in groups of " << k << ": ";
    printList(head);

    return 0;
}