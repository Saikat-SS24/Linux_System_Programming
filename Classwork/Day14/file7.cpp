#include <iostream>
using namespace std;

//call by values
void swap_value(int a, int b)
{
    int t=0;
    t = a;
    a=b;
    b=t;
    cout<<"\n[Inside swap_value] a="<<a<<"\tb="<<b<<endl;
}

//call by pointer
void swap_ptrs(int *a, int *b)
{
    int t=0;
    t = *a;
    *a=*b;
    *b=t;
    cout<<"\n[Inside swap_ptrs] a="<<*a<<"\tb="<<*b<<endl;
}


//call by reference
void swap_ref(int &a, int &b)
{
    int t=0;
    t = a;
    a=b;
    b=t;
    cout<<"\n[Inside swap_ref] a="<<a<<"\tb="<<b<<endl;
}


int main()
{
    int a=10,b=20;
    cout<<"Before swapping "<<endl;
    cout<<"\n[main function] a="<<a<<"\tb="<<b<<endl;
    swap_value(a,b);
    cout<<"After swapping "<<endl;
    cout<<"\n[main function] a="<<a<<"\tb="<<b<<endl;
    
    
    cout<<"Before swapping "<<endl;
    cout<<"\n[main function] a="<<a<<"\tb="<<b<<endl;
    swap_ptrs(&a,&b);
    cout<<"After swapping "<<endl;
    cout<<"\n[main function] a="<<a<<"\tb="<<b<<endl;
    
    cout<<"Before swapping "<<endl;
    cout<<"\n[main function] a="<<a<<"\tb="<<b<<endl;
    swap_ref(a,b);
    cout<<"After swapping "<<endl;
    cout<<"\n[main function] a="<<a<<"\tb="<<b<<endl;
    return 0;
}

