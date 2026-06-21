/*
function  ptrs
*/

#include <iostream>

using namespace std;

int add(int, int);
int mul(int, int);

int main()
{
    int (*fPtr)(int, int);

    fPtr = add;
    int ret = fPtr(10,20);
    cout<<ret<<endl;
    fPtr = mul;
    ret = fPtr(2,3);
    cout<<ret<<endl;
    
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

