#include <iostream>
#define CAP 5

using namespace std;

int StackArr[CAP];

int top;
int bottom=-1;

void push(int val)
{
    if(top == CAP-1)
    {
        cout<<"\nStack is full"<<endl;
        return;
    }
    StackArr[++top] = val;
    
}

void pop()
{
    if(top == bottom)
    {
        cout<<"\nStack is empty"<<endl;
        return;
    }
    cout<<"\nPopped out "<<StackArr[top]<<" element"<<endl;
    top--;
}

void display()
{
    if(top == bottom)
    {
        cout<<"\nStack is empty"<<endl;
        return;
    }
    for(int i=top;i>=0;i--)
        cout<<StackArr[i]<<endl;
}

int main()
{
    top = bottom;
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    push(60);
    display();

    pop();
    pop();
    pop();
    pop();
    pop();
    pop();
    display();

    return 0;
}