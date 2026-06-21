/*
DMA
malloc
calloc
realloc
free

arr[0]  arr[1]  arr[2]
2000    2004    2008
10      20      30
ptr++   ptr++   ptr++ =>garbage
*/

#include <iostream>
#include <stdlib.h>

using namespace std;


void display(int *, int);

int main()
{
    //int arr[3] = {10,20,30};
    //int *ptr = arr; //2000 (BA)


    //display(ptr, 3);

    //int a; //stack mem location BA 2000
    int *ptr = nullptr;

    //ptr = &a; //ptr = 2000
    ptr =(int *)malloc(sizeof(int)); //BA 2000

    *ptr = 10;

    cout<<*ptr<<endl;


    free(ptr);

    return 0;
}

void display(int *list,int count)
{
    cout<<"\nThe list is \n";
    for(int i=0;i<count;i++)
        cout<<list[i]<<" ";
    cout<<"\n";
}