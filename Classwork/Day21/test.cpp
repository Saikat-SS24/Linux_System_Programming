#include<iostream>
#include<exception>
using namespace std;

int main()
{
    try{
        int a = 10;
        int b = 0;
        if(b == 0)
            throw "Divide by zero error";
        int c = a/b;
    }
    catch(const char *e)
    {
        cout << "\nException: " << e << endl;
    }

    return 0;
}