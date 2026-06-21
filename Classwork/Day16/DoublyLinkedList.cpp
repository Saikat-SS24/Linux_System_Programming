#include <iostream>
using namespace std;

// Define the Node structure
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Function to add a node at the end
void insert(Node** head, int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Traverse from Head to Tail
void displayForward(Node* head) {
    cout << "Forward Traversal: ";
    while (head != NULL) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

// Traverse from Tail to Head
void displayBackward(Node* head) {
    if (head == NULL) return;

    // 1. Go to the last node
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // 2. Traverse backward using 'prev'
    cout << "Backward Traversal: ";
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->prev;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = NULL;
    int choice, val;

    // Quick list creation
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);

    cout << "List created with values: 10, 20, 30" << endl;
    cout << "1. Forward Traversal\n2. Backward Traversal\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        displayForward(head);
    } else if (choice == 2) {
        displayBackward(head);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}