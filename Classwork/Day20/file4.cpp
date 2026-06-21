#include <iostream>
using namespace std;

class Calculator
{

public:
    int addition(int v1, int v2)
    {
        return v1+v2;
    }

    float addition(float v1, float v2)
    {
        return v1+v2;
    }
};

int main()
{
    Calculator objCalc;
    cout<<objCalc.addition(10,20)<<endl;
    cout<<objCalc.addition(10.1f,20.2f)<<endl;

    return 0;
}