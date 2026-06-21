#include <stdio.h>

int main()
{
    int i=10;
    float f = i;
    printf("\n%d\t%f\n",i,f);

    f = 20.55f;
    i = f;
    printf("\n%d\t%f\n",i,f);


    return 0;
}