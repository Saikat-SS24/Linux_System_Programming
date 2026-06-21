#include<iostream>
using namespace std;

namespace MyNameSpace
{
    int val = 100;
    void display(){
        cout << "\nInside MyNameSpace" << endl;
    }
}

int main()
{
    cout << "\nValue " <<  MyNameSpace::val << endl;
    MyNameSpace::display();

    return 0;
}