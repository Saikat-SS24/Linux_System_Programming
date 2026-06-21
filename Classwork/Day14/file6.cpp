/*

types of pointer
1. wild pointer
2. NULL pointer
3. void / generic pointer
4. dangling pointer
*/
#include <iostream>
using namespace std;

int *sum(int v1)
{
    static int ret=10;
    ret = ret * v1;
    return &ret;
}

int main()
{
    /*
    int *ptr1; //wild ptr
    int *ptr2 = nullptr; //NULL pointer

    int arr[3] = {10,20,30};

    void *ptr3=nullptr; //generic pointer

    double arr1[3] = {1.1,2.2,3.3};
    double *dptr =nullptr;
    ptr2 = arr;
    ptr2++; //=>ptr arthematic next element by moving by 4 bytes

    dptr = arr1;
    dptr++; //=>dptr arthematic next element by moving by 8 bytes
    */

    /*
    int *ptr = sum(10); //ptr is pointing to the lost address => dangling ptr 
    cout<<"ret = "<<*ptr<<endl;
    */
    int *ptr = sum(10);  
    cout<<"ret = "<<*ptr<<endl;


}