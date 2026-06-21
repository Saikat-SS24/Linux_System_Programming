/*
Pointers
to point to the (BA of an variable)/BA
are ment to point to an address

dec:

dt *ptrName;

int *ptr;

pointer does not belong to a DT
it points to a address which might be of certain DT

use of ptr

int a=10; //2000 = 10

int *ptr;

ptr = &a; => ptr-> 2000
ptr = 2000
*/

#include <iostream>

using namespace std;


int main()
{
    int a=10;
    int arr[3] = {101,201,301};
    int *ptr=nullptr;

    ptr = &a;

    
    //*ptr = 20;
    printf("\na address = %u and value stored = %d",&a,a);
    //a = 20;
    printf("\nvalue pointed by ptr = %d",*ptr);
    
    ptr = &arr[0]; //BA of the array;

    printf("\nBA of array = %u and ptr(%u) is storing %u",&arr[0], &ptr, ptr);

    printf("\narr[0] = %d\t *ptr=%d",arr[0],*ptr);
    ptr = ptr+1; //BA + sizeof(dt)*iv
    printf("\narr[1] = %d\t *ptr=%d",arr[1],*ptr);
    ptr+=1; //BA + sizeof(dt)*iv
    printf("\narr[2] = %d\t *ptr=%d",arr[2],*ptr);
    

    printf("\n\n");
    return 0;

}