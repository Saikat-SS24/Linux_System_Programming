/*
demo on I/O Statements

*/

#include <iostream>

using namespace std;

int main()
{
    int a;
    float f;
    char ch;
    char str1[20];

    scanf("%c%d%f%s", &ch,&a,&f,str1);


    printf("\nch = %c",ch);
    printf("\na = %d",a);
    printf("\nf = %f",f);
    printf("\nstr1 = %s\n",str1);

    return 0;
    
}