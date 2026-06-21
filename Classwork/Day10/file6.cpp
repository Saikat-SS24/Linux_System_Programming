#include <iostream>

using namespace std;



int f1(int v1)
{
    static int xFactor = 3;
    xFactor = xFactor + v1;
    return (xFactor);
}

// void f2()
// {
//     xFactor = 6;
// }


int main()
{
    int retValue=0;

    retValue = f1(10);

    cout<<"retValue="<<retValue<<endl;

    retValue = f1(10);

    cout<<"retValue="<<retValue<<endl;
    // f2();

    retValue = f1(10);

    cout<<"retValue="<<retValue<<endl;
    

    return 0;

}