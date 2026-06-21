#include <iostream>
//#define MAX_SIZE 10
using namespace std;

//int SIZE = 10;
extern int SIZE;
int main()
{
    int arr[SIZE];

    cout<<"Size of the array="<<sizeof(arr)<<" bytes"<<endl;

    return 0;

}