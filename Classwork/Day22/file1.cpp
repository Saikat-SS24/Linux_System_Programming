#include<iostream>
using namespace std;

class DivideByZeroException
{
    public:
        const char *what() const{
            return "Error: Divide by zero is not allowed";
        }
};

int main()
{
    int a = 10, b = 0;
    try{
        if(b == 0){
            throw DivideByZeroException();
        }
        int res = a/b;
        cout << "\nResult: " << res << endl;
    }
    catch(DivideByZeroException e)
    {
        cout << e.what() << endl;
    }
    cout << "\nProgram continues" << endl;

    return 0;
}