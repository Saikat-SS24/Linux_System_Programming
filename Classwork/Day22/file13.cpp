/*
class specialization

*/

#include <iostream>
#include <cstring>
using namespace std;


template <class T>
class Calulator
{
private:
    T a,b;
public:
    Calulator(T x, T y): a(x), b(y) {}

    T add(){ return a+b; }

};


//full specialization of class template
template <>
class Calulator<const char *>
{
private:
    const char* a;
    const char *b;
public:
    Calulator(const char *x, const char *y): a(x), b(y) {}

    const char *add(){ 
        size_t len = strlen(a)+strlen(b)+1;
        char *res = new char[len];  
        strcpy(res, a);
        strcat(res,b);  
        return res;
    }

};


int main()
{
    //Numeric additions
    Calulator <int> c1(10,20);
    cout<<c1.add()<<endl;

    Calulator <float> c2(10.4,20.3);
    cout<<c2.add()<<endl;

    Calulator <const char *>c3("abc1","xyz");
    const char *res = c3.add();
    cout<<"Res: "<<res<<endl;
    delete [] res;


    return 0;
}
