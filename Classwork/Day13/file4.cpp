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
    int *ptr=nullptr;

    ptr = &a;

    printf("\na address = %u and value stored = %d",&a,a);
    printf("\nAddress of ptr = %u\n",&ptr);
    printf("\nptr(%u) is pointing to %u address\n",&ptr,ptr);
    printf("\nsize of ptr = %d",sizeof(ptr));
    printf("\n\n");
    return 0;

}