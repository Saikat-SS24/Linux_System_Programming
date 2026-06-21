#include <iostream>
using namespace std;

namespace Soumi{
    void show()
    {
        cout<<"\nHello, Bhima"<<endl;
    }

    void d1()
    {
        cout<<"\n[Soumi] Hello, d1"<<endl;
    }
}

namespace Vandhana{
    void show()
    {
        cout<<"\nHello, Shankar"<<endl;
    }
    void d1()
    {
        cout<<"\n[Vandana] Hello, d1"<<endl;
    }
}

using namespace Soumi;


void display()
{
   // using namespace Vandhana;
    show();
}

int main()
{
    //using namespace Soumi;
    using Vandhana::d1;
    show();
    show();
    d1();

    display();

    return 0;
}