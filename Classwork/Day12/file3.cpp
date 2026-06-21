// linear search
#include <iostream>
#define SIZE 10

using namespace std;

int main()
{
    int arr[SIZE];
    int key=0, iv=0;
    cout<<"\nEnter the "<<SIZE<<" elements of the array"<<endl;

    for(int i=0;i<SIZE;i++)
    {
        cout<<"\nEnter "<<i<<" value of array element: ";
        cin>>arr[i];
        //scanf("%d",&arr[i]);
    }

    //display array elements
    for(int i =0;i<SIZE;i++)
        cout<<arr[i]<<"\t";
    cout<<endl;

    cout<<"\nEnter the key value to be searched in array: ";
    cin>>key;

    for(iv=0;iv<SIZE;iv++)
    {
        if(arr[iv]==key)
            break;
    }

    if(iv > (SIZE-1))
        cout<<key <<" value was not found in the list"<<endl;
    else
        cout<<key<<" value is found in the "<<iv<<" location in the list"<<endl;

    return 0;
}