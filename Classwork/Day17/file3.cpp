#include <iostream>
using namespace std;

int binarySearch(int arr[], int size, int key)
{
    static int count=0;
    int low=0, high=size-1;
    int mid;
    
    while(low <= high)
    {
        cout<<"Count (iter) = "<<count++<<endl;
        mid = low + (high - low)/2;
        cout<<"mid = "<<arr[mid]<<" idx="<<mid<<" low:"
        <<low<<" high: "<<high<<endl;
        if(arr[mid] == key)
            return mid;
        if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    int a[] = {12,13,21,41,91,450,455,636};
    int cap = sizeof(a)/sizeof(a[0]);
    int key=112;
    int ret = binarySearch(a,cap,key);

    if(ret <0)
        cout<<key<<" Not found"<<endl;
    else
        cout<<key<<" found at "<<ret<<" pos"<<endl;

    return 0;
}