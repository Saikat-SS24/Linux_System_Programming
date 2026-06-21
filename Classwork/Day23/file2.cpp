#include <iostream>
#include <array>

using namespace std;


int main()
{
    //2D array
    array <array<int,3>,2> a = {{
        {{1,2,3}},
        {{4,5,6}}
    }};

    cout<<a[0][2]<<endl;
    return 0;
}