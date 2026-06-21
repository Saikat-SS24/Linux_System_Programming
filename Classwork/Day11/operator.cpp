#include <iostream>

using namespace std;

int main()
{
    int a=100,b=201,c=301;

    int res=0;

    //res = (a>b)?(110):(201);


    res = (a>b)?((a>c)?(a):(c)):((b>c)?(b):(c));

    cout<<"res="<<res<<endl;

    return 0;
}