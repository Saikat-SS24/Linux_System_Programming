/*
arr[] = {1,2,3,4,3,5};
         0,1,2,3,4,5 =>idx values
quicksort(arr)
arr[] = {1,2,3,3,4,5};
         0,1,4,2,3,5
         0,1,2,3,4,5



*/
#include <iostream>

using namespace std;

void swapElem(int *v1, int *v2)
{
    int t=*v1;
    *v1 = *v2;
    *v2 = t;
}

void bubbleSort(int arr[], int size)
{

    for(int i=0;i<size-1;i++)
    {
        for(int j=0;j<size-1-i;j++)
        {
            if(arr[i]<arr[j]) //< for asc, and > for desc
                swapElem(&arr[i],&arr[j]);
        }
    }
}

void display(int arr[], int size)
{
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

int main()
{
    int aList[] = {2,1,5,8,3,9};
    int Cap = sizeof(aList)/sizeof(aList[0]);
    cout<<"Before sorting"<<endl;
    display(aList, Cap);
    bubbleSort(aList,Cap);
    cout<<"After sorting"<<endl;
    display(aList, Cap);

    return 0;
    
}