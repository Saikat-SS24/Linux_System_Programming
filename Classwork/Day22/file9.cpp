/*

template <typename T>
return_type fName(T inputParams)
{
}


template <class T>
return_type fName(T inputParams)
{
}

*/

#include <iostream>
using namespace std;



//generic function for addition of two variables
template <typename T>

T addition(T v1,T v2)
{
    T result = v1+v2;
    return result;
}

int main()
{
    int a=10,b=20;
    float x=30.3f,y=44.4f;

    cout<<addition(a,b)<<endl;
    cout<<addition(x,y)<<endl;
    string fName="Saikat", sName="Sheet";
    cout<<addition(fName,sName)<<endl;
    cout<<addition('A','B')<<endl;

    return 0;
}
