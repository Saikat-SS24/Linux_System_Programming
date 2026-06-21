#include <iostream>

using namespace std;

void display(const int [], int);

void display1(int [], int);
void display2(const int [], int);

int main()
{
    int arr[5] = {10,20,30,40,50};

    display(arr, sizeof(arr)/sizeof(arr[0]));
    display1(arr,125);
    display(arr, 5);
    display2(arr,121);
    display(arr,5);
    return 0;
}


void display(const int list[], int count)
{
    for(int i=0;i<count;i++)
        cout<<list[i]<<"\t"<<endl;
}

void display1(int list[], int key)
{
    list[1] = key;
}

void display2(const int list[], int key)
{
    //list[1] = key;
}