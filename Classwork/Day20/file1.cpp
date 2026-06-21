/*
Demo on this operator
'this' is an internal pointer towards the class where it is used
*/
#include <iostream>
using namespace std;

class A
{
private:
    int a;
    int b;
public:
    A() { cout<<"\nDef Cstr called\n"; a = 0; b=0; }
    A(int a, int b) { cout<<"\nPara Cstr called\n"; this->a = a; this->b=b; }
    void setA(int a){ this->a = a; }
    int getA() { return a; }
    void setB(int b){ this->b = b; }
    int getB() { return this->b; }
    void dispA() { cout<<"\nA = "<<this->a<<endl; cout<<"\nB = "<<b<<endl; }
};

int main()
{
    A objA(10,20);

    objA.dispA();

    objA.setA(20);
    objA.dispA();

    return 0;
}