#include <iostream>
#define CAP 5

using namespace std;

int QueueArr[CAP];

int rare;
int front;

void enqueue(int val)
{
    if(rare == CAP)
    {
        cout<<"\nQueue is full"<<endl;
        return;
    }
    QueueArr[rare++] = val;
    
}

void dequeue()
{
    if(front == rare)
    {
        if(front == CAP)
        {
            //reset
            rare = 0;
            front = 0;
        }
        cout<<"\nQueue is empty"<<endl;
        return;
    }
    cout<<"Dequeued "<<QueueArr[front++]<<endl;

}

void display()
{
    if(front == rare)
    {
        cout<<"\nQueue is empty"<<endl;
        return;
    }

    for(int i=front;i<rare;i++)
        cout<<QueueArr[i]<<" ";
    cout<<endl;
}

int main()
{
    rare = 0;
    front = 0;
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    enqueue(60);
    display();

    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    display();


    enqueue(101);
    enqueue(201);
    enqueue(301);
    display();
    return 0;
}