/*
function  ptrs
*/

#include <iostream>

using namespace std;

int add(int, int);
int mul(int, int);

int main()
{
    int (*fPtr[2])(int, int) = {add,mul}; //define the seq of functions to be called

    for(int i=0;i<2;i++)
        cout<<fPtr[i](10,20)<<endl;
    
    return 0;
    
}

int add(int v1, int v2)
{
    return v1+v2;
}

int mul(int v1, int v2)
{
    return v1*v2;
}

