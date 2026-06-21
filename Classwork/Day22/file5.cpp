#include <iostream>
#include <memory>
using namespace std;

/*
1. auto_ptr -> Deprecated //not in use
2. unique_ptr
3. shared_ptr
4. weak_ptr


*/

int main()
{
    auto_ptr<int> ptr1(new int(10)); //auto_ptr was removed from c++17
    cout<<*ptr1<<endl;

    auto_ptr<int> ptr2 = ptr1; //ownership change
    cout<<*ptr2<<endl;
    cout<<"\n dereferening ptr1\n";
    cout<<*ptr1<<endl;

    return 0;
}

