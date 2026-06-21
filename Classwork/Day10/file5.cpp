/*
demo of storage class

*/

#include <iostream>

using namespace std;

int main()
{

    int i=10; //stack mem
    cout<<"i="<<i<<endl;

    //34 times j is getting access i.e y store in reg
    register int j=0;
    for(j=0;j<10;j++)
        cout<<"j="<<j<<endl;
    
    cout<<"\nAddress of (RAM) i="<<&i<<endl;
    cout<<"\nAddress of (CPU) j="<<&j<<endl;
    



    return 0;
}