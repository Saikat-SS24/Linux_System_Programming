/*
Polymorphism

1. compile time polymorphism - Overloading of the function
- Static binding

*/

#include <iostream>
using namespace std;


int addition(int , int );
float addition(float, float);



int main()
{
    cout<<addition(10,20)<<endl;
    cout<<addition(10.5f,20.5f)<<endl;

    return 0;
}

int addition(int v1, int v2)
{
    cout<<"Addition of 2 ints"<<endl;
    return v1+v2;
}

float addition(float v1, float v2)
{
    cout<<"Addition of 2 floats"<<endl;
    return v1+v2;
}