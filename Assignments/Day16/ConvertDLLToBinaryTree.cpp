/* Convert DLL to Binary Tree (Level Order)
Convert a doubly linked list into a binary tree in level order */

#include <iostream>
#include <queue>
using namespace std;

// Using the same structure for both DLL and Binary Tree
struct Node {
    int data;
    Node* prev; // Acts as 'left' in Tree
    Node* next; // Acts as 'right' in Tree
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

Node* convertDLLToBinaryTree(Node* head) {
    if (head == nullptr) return nullptr;

    // Queue to store parent nodes for level order assignment
    queue<Node*> q;

    // The head of the DLL is the root of the tree
    Node* root = head;
    q.push(root);

    // Advance the DLL pointer to the next potential child
    head = head->next;

    while (head != nullptr) {
        // Get the current parent from the queue
        Node* parent = q.front();
        q.pop();

        // 1. Assign Left Child
        Node* leftChild = head;
        head = head->next; // Move DLL pointer
        leftChild->prev = leftChild->next = nullptr; // Clear DLL links
        parent->prev = leftChild; // parent->left = leftChild
        q.push(leftChild);

        // 2. Assign Right Child (if it exists)
        if (head != nullptr) {
            Node* rightChild = head;
            head = head->next; // Move DLL pointer
            rightChild->prev = rightChild->next = nullptr; // Clear DLL links
            parent->next = rightChild; // parent->right = rightChild
            q.push(rightChild);
        }
    }
    return root;
}

// Function to print tree in level order to verify
void printLevelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->prev) q.push(curr->prev);
        if (curr->next) q.push(curr->next);
    }
}

int main() {
    // Create DLL: 10 <-> 20 <-> 30 <-> 40 <-> 50
    Node* head = new Node(10);
    Node* n2 = new Node(20);
    Node* n3 = new Node(30);
    Node* n4 = new Node(40);
    Node* n5 = new Node(50);

    head->next = n2; n2->prev = head;
    n2->next = n3; n3->prev = n2;
    n3->next = n4; n4->prev = n3;
    n4->next = n5; n5->prev = n4;

    Node* root = convertDLLToBinaryTree(head);

    cout << "Binary Tree (Level Order): ";
    printLevelOrder(root);
    cout << endl;

    return 0;
}