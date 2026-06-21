#include <iostream>
#include <cstdlib>


using namespace std;

typedef struct node
{
    int val;
    struct node *next;
}NODE;

void *createNode();
NODE *insertEnd(NODE *);

void displayList(NODE *);
int dispMenu();

int main()
{
    NODE *head=nullptr;
    while(1){
            switch(dispMenu())
            {
                case 1:
                        //inserting new element
                        head = insertEnd(head);
                        break;
                case 2:
                        //display of the list
                        displayList(head);
                        break;
                case 3:
                        //exit
                        exit(EXIT_SUCCESS);
                        break;
                default:
                        cout<<"\nEnter the correct choice";
            }
    }
}


int dispMenu()
{
    int ch;
    cout<<"\nLinked List Menu"<<endl;
    cout<<"\nPress, ";
    cout<<"\n1. Creating New Node";
    cout<<"\n2. Display List";
    cout<<"\n3. exit";
    cout<<"\nChoice: ";
    cin>>ch;
    return ch;
}

void *createNode()
{
    return (malloc(sizeof(NODE)));
}

NODE *insertEnd(NODE *head)
{
    NODE *temp = nullptr;
    NODE *nn=nullptr;
    nn = (NODE *)createNode();
    cout<<"\nEnter the value of new node: ";
    cin>>nn->val;
    nn->next = nullptr;

    temp = head;
    if(head == nullptr)
    {
        //list is empty
        head = nn;
        temp = head;
        return head;
    }
    else
    {
        while(head->next != nullptr)
            head = head->next;
        head->next = nn;
    }
    head = temp;
    return head;
}


void displayList(NODE *head)
{
    cout<<"\nList is\n";
    while(head != nullptr){
        cout<<head->val<<"->";
        head = head->next;
    }
    cout<<"NULL"<<endl;
}