/*

function defined (by how they are called),
1. pass by value
2. pass by pointer
3. pass by reference

*/

#include <iostream>

using namespace std;

int addition(int, int); 

int main()
{
    int ret=0;
    int a=20, b=30;
    ret = addition(a,b); //pass by value

    cout<<ret<<endl;


    return 0;
}

int addition(int v1, int v2)
{
    return v1+v2;
}