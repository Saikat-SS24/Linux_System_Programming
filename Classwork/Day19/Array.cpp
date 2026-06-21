#include <iostream>
#include "Array.h"
using namespace std;



Array::Array(){ ptr = new int; Cap = 1; } //default constr
Array::Array(int n) {
    #ifdef DEBUG
        cout<<"\npara got invoked\n";
    #endif 
    ptr = new int[n]; Cap = n; } // para cnstr
Array::~Array() { 
    #ifdef DEBUG
        cout<<"\nDestr got called\n";
    #endif
    delete [] ptr;
}

void Array::swapElem(int &v1, int &v2)
{
    int t = v1; v1=v2; v2=t;
}

void Array::getValue(){
    cout<<"\nEnter the "<<Cap<<" values of the array\n";
    for(int i=0;i<Cap;i++)
        cin>>ptr[i];
}

void Array::dispArr()
{
    cout<<"\n===============\n";
    cout<<"\nList is\n";
    cout<<"\n===============\n";
    for(int i=0;i<Cap;i++)
        cout<<ptr[i]<<endl;
    cout<<"\n===============\n";
}

void Array::sort()
{
    bubbleSort();
}


void Array::bubbleSort()
{
    #ifdef DEBUG
        cout<<"\nSorting in Progress\n";
    #endif
    for(int i=0;i<Cap;i++)
    {
        for(int j=0;j<Cap-1-i;j++)
        {
            if(ptr[j]>ptr[j+1])
            {
                //swap
                swapElem(ptr[j], ptr[j+1]);
            }
        }
    }
    #ifdef DEBUG
    cout<<"\nSorting Done!\n";
    #endif
}
