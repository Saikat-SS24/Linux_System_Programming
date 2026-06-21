#include <iostream>
using namespace std;

typedef struct node
{
    int val;
    struct node *prev;
    struct node *next;
} NODE;

// Prototypes
NODE* createNode(int);
NODE* insertBegin(NODE*);
NODE* insertEnd(NODE*);
NODE* insertAtPos(NODE*);
NODE* deleteBegin(NODE*);
NODE* deleteEnd(NODE*);
NODE* deleteByValue(NODE*);
void searchElement(NODE*);
void displayForward(NODE*);
void displayBackward(NODE*);
void freeList(NODE*);
int dispMenu();

int main()
{
    NODE *head = nullptr;

    while (1)
    {
        switch (dispMenu())
        {
            case 1: head = insertBegin(head); break;
            case 2: head = insertEnd(head); break;
            case 3: head = insertAtPos(head); break;
            case 4: head = deleteBegin(head); break;
            case 5: head = deleteEnd(head); break;
            case 6: head = deleteByValue(head); break;
            case 7: searchElement(head); break;
            case 8: displayForward(head); break;
            case 9: displayBackward(head); break;
            case 10:
                freeList(head);
                exit(0);
            default:
                cout << "\nInvalid choice\n";
        }
    }
}

int dispMenu()
{
    int ch;
    cout << "\n\n===== Doubly Linked List Menu =====\n";
    cout << "1. Insert at Beginning\n";
    cout << "2. Insert at End\n";
    cout << "3. Insert at Position\n";
    cout << "4. Delete from Beginning\n";
    cout << "5. Delete from End\n";
    cout << "6. Delete by Value\n";
    cout << "7. Search Element\n";
    cout << "8. Display Forward\n";
    cout << "9. Display Backward\n";
    cout << "10. Exit\n";
    cout << "Enter choice: ";
    cin >> ch;
    return ch;
}

// Create Node
NODE* createNode(int val)
{
    NODE* nn = (NODE *)malloc(sizeof(NODE));
    nn->val = val;
    nn->prev = nn->next = nullptr;
    return nn;
}

// Insert at Beginning
NODE* insertBegin(NODE* head)
{
    int val;
    cout << "Enter value: ";
    cin >> val;

    NODE* nn = createNode(val);

    if (head)
    {
        nn->next = head;
        head->prev = nn;
    }

    return nn;
}

// Insert at End
NODE* insertEnd(NODE* head)
{
    int val;
    cout << "Enter value: ";
    cin >> val;

    NODE* nn = createNode(val);

    if (!head)
        return nn;

    NODE* temp = head;
    while (temp->next)
        temp = temp->next;

    temp->next = nn;
    nn->prev = temp;

    return head;
}

// Insert at Position
NODE* insertAtPos(NODE* head)
{
    int val, pos;
    cout << "Enter value & position: ";
    cin >> val >> pos;

    if (pos == 1)
        return insertBegin(head);

    NODE* nn = createNode(val);
    NODE* temp = head;

    for (int i = 1; temp && i < pos - 1; i++)
        temp = temp->next;

    if (!temp)
    {
        cout << "Invalid position\n";
        delete nn;
        return head;
    }

    nn->next = temp->next;
    nn->prev = temp;

    if (temp->next)
        temp->next->prev = nn;

    temp->next = nn;

    return head;
}

// Delete from Beginning
NODE* deleteBegin(NODE* head)
{
    if (!head)
    {
        cout << "List empty\n";
        return head;
    }

    NODE* temp = head;
    head = head->next;

    if (head)
        head->prev = nullptr;

    free(temp);
    return head;
}

// Delete from End
NODE* deleteEnd(NODE* head)
{
    if (!head)
        return nullptr;

    if (!head->next)
    {
        delete head;
        return nullptr;
    }

    NODE* temp = head;
    while (temp->next)
        temp = temp->next;

    temp->prev->next = nullptr;
    free(temp);

    return head;
}

// Delete by Value
NODE* deleteByValue(NODE* head)
{
    int val;
    cout << "Enter value to delete: ";
    cin >> val;

    if (!head)
        return head;

    NODE* temp = head;

    while (temp && temp->val != val)
        temp = temp->next;

    if (!temp)
    {
        cout << "Value not found\n";
        return head;
    }

    if (temp == head)
        return deleteBegin(head);

    if (!temp->next)
        return deleteEnd(head);

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    free(temp);
    return head;
}

// Search
void searchElement(NODE* head)
{
    int val, pos = 1;
    cout << "Enter value to search: ";
    cin >> val;

    while (head)
    {
        if (head->val == val)
        {
            cout << "Found at position " << pos << endl;
            return;
        }
        head = head->next;
        pos++;
    }

    cout << "Not found\n";
}

// Display Forward
void displayForward(NODE* head)
{
    cout << "\nForward: ";
    while (head)
    {
        cout << head->val << " <-> ";
        head = head->next;
    }
    cout << "NULL\n";
}

// Display Backward
void displayBackward(NODE* head)
{
    if (!head)
        return;

    NODE* temp = head;

    while (temp->next)
        temp = temp->next;

    cout << "\nBackward: ";
    while (temp)
    {
        cout << temp->val << " <-> ";
        temp = temp->prev;
    }
    cout << "NULL\n";
}

// Free entire list
void freeList(NODE* head)
{
    NODE* temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    cout << "Memory freed successfully\n";
}