#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct node
{
    int val;
    struct node *ptr;
}NODE;


int main()
{
    //creating the nodes
    NODE n1,n2,n3;

    //initializing values
    n1.val = 10;
    n1.ptr = nullptr;
    n2.val = 20;
    n2.ptr = nullptr;
    n3.val = 30;
    n3.ptr = nullptr;
    
    //make a relationship
    n1.ptr = &n2;
    n2.ptr = &n3;


    printf("\nAddress n1 = %u",&n1);
    printf("\nAddress n2 = %u",&n2);
    printf("\nAddress n3 = %u",&n3);


    printf("\n n1.ptr = %u",n1.ptr);
    printf("\n n2.ptr = %u",n2.ptr);
    cout<<endl;
    //traverse the list
    NODE *head = nullptr;

    head = &n1; // point head to BA of list

    cout<<n1.val<<endl;
    cout<<head->val<<endl;

    //head = &n2;
    //head = n1.ptr;
    head = head->ptr;//=>BA of n2
    cout<<n2.val<<endl;
    cout<<head->val<<endl;

    //head = &n3;
    //head = n2.ptr;
    head = head->ptr;//BA of n3
    cout<<n3.val<<endl;
    cout<<head->val<<endl;

    //traverse using loop
    head = &n1;

    while(head != nullptr)
    {
        cout<<head->val<<"->";
        head = head->ptr;
    }
    cout<<"NULL"<<endl;






    
    


    return 0;
}