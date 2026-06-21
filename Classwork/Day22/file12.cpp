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
template <typename T>

T addition(T v1,T v2)
{
    
        return v1+v2;  
    
}

template <>
const char *addition<const char *>(const char *v1, const char *v2)
{
    //full specialization of templates
    char *res = new char[200];
    strcpy(res,v1);
    strcat(res,v2);
    return res;

}




int main()
{
    int a=10,b=20;
    float x=30.3f,y=44.4f;

    cout<<addition(a,b)<<endl;
    cout<<addition(x,y)<<endl;
    cout<<addition('a','b')<<endl;
    const char *res = addition("abc1", "abc2");
    cout<<res<<endl;
    
    delete []res; //important to release the resource
    
    return 0;
}
