
#include <iostream>
#include "file11.h"

template <typename T> 
Stack<T>::Stack() { top = -1; }

template <typename T>
void Stack<T>::push(T val)
{
    if(isFull()){
        cout<<"\nStack is Full"<<endl;
        return;
    }
    top++;
    st[top]=val;
}

template <typename T>
T Stack<T>::pop()
{
    if(isEmpty())
    {
        cout<<"\nStack is Empty"<<endl;
    }
    T popped_ele = st[top];

    top--;
    return popped_ele;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}

template <typename T>
bool Stack<T>::isFull()
{
    if(top == (SIZE -1))
        return 1;
    else
        return 0;
}


template <typename T>
T Stack<T>::topElement()
{
    return st[top];
}
