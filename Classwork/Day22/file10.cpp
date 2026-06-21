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
#include <typeinfo>
#include <cstring>
using namespace std;



//generic function for addition of two variables
template <typename T1, typename T2>

T1 addition(T1 v1,T2 v2)
{
    
        return v1+v2;  
    
}


template <class T>
T findMax(T v1, T v2)
{
    return ((v1>v2)?v1:v2);
}

int main()
{
    int a=10,b=20;
    float x=30.3f,y=44.4f;

    cout<<addition(a,b)<<endl;
    cout<<addition(x,y)<<endl;
    cout<<addition('a','b')<<endl;

    
    cout<<findMax(10,23)<<endl;
    cout<<findMax(110.1,2.3)<<endl;
    cout<<findMax('A','B')<<endl;
        
    
    return 0;
}
