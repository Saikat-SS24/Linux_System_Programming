#include <iostream>
#include <stdlib.h>

using namespace std;


int main()
{

    //int *ptr = (int *)malloc(sizeof(int)*3);
    int n,n1;
    cout<<"\nEnter the size of the array: ";
    cin>>n;
    int *ptr = (int *)calloc(n, sizeof(int));

    int *temp = ptr;

    for(int i=0;i<n;i++)
        cout<<*ptr++<<endl;

    ptr = temp;

    for(int i=0;i<n;i++)
        cin>>*ptr++;
    
    ptr = temp;

    for(int i=0;i<n;i++)
        cout<<*ptr++<<endl;
    
    ptr = temp;

    for(int i=0;i<n;i++)
        cout<<"\tAddress = "<<(unsigned long long int*)ptr<<" Value = "<<*ptr++<<endl;


    cout<<"\nEnter the size of the array to be extended: ";
    cin>>n1;

    ptr = temp;
    int *temp1=nullptr;
    temp1 = (int *)realloc(ptr, n1*sizeof(int));
    
    ptr = temp1;

    for(int i=0;i<n1;i++)
        cout<<"\tAddress = "<<(unsigned long long int*)ptr<<" Value = "<<*ptr++<<endl;

    ptr = temp1;
    for(int i=0;i<n;i++,ptr++);
    
    for(int i=n;i<n1;i++)
        cin>>*ptr++;
    
    ptr = temp1;

    for(int i=0;i<n1;i++)
        cout<<"\tAddress = "<<(unsigned long long int*)ptr<<" Value = "<<*ptr++<<endl;

    ptr = temp1;

    free(ptr);

    return 0;
    
}