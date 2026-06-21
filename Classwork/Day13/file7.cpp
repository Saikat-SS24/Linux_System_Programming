/*
thumb rules

1. [] to *
    ex: op[] <=> *op vice versa
        op[1] <=> *(op+1) 

2. &* => nullify each other
    ex: &*op <=> op


*/

#include <iostream>

using namespace std;

int main()
{
    int arr[3] = {101,201,301};
    int *ptr = nullptr;

    printf("\narr[0] = %d",arr[0]);
    printf("\narr[0] = %d",*(arr+0));
    printf("\narr[1] = %d",*(arr+1)); //ptr expr
    printf("\narr[2] = %d",*(arr+2));

    //ptr = &arr[0];
    ptr = arr;
    printf("\narr[0] (ptr) = %d",*(ptr+0)); //101
    printf("\narr[1] (ptr) = %d",*(ptr+1)); //201
    printf("\narr[2] (ptr) = %d",*(ptr+2)); //301

    printf("\narr[0] (ptr) = %d",ptr[0]); //101 //array expr
    printf("\narr[1] (ptr) = %d",ptr[1]); //201
    printf("\narr[2] (ptr) = %d",ptr[2]); //301



    
    

    printf("\n\n");

    return 0;

}