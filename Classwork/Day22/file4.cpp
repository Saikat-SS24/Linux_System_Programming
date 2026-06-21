#include <iostream>
using namespace std;

//Nesting of namespace

namespace Outer
{
    void f1()
    {
        cout<<"\n[Outer]Inside f1"<<endl;
    }

    namespace Inner
    {
        void f1()
        {
            cout<<"\n[Inner]Inside f1"<<endl;
        }
    }
}


namespace Outer{
    void f2()
    {
        cout<<"\n[Outer]Inside f2"<<endl;
    }
}

int main()
{

    Outer::Inner::f1();
    Outer::f1();
    Outer::f2();
    return 0;
}