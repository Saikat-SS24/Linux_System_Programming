#include <iostream>
#include <set>
using namespace std;

int main()
{
    // Creating an empty multiset of integers
    multiset<int> ms1;
    // Initialize with initializer list
    multiset<int> ms2 = {5, 3, 3, 1};
    // Print elements (automatically sorted)
    for (auto i : ms2)
        cout << i << " ";
    cout<<endl;

    ms2.insert(10);
    ms2.insert(5);

    // Print elements (automatically sorted)
    for (auto i : ms2)
        cout << i << " ";
    cout<<endl;

    

    return 0;
}