#include <stdio.h>


int main()
{
    const int a=10;
    int *ptr=NULL;

    ptr = &a;

    
    *ptr = 20;
    printf("\na address = %u and value stored = %d",&a,a);
    //a = 20;
    printf("\nvalue pointed by ptr = %d",*ptr);
    
    printf("\n\n");
    return 0;

}