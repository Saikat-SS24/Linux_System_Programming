/*

Array - stl container

*/

// C++ code to demonstrate working of array,
// at() and get()
#include<iostream>
#include<array> // for array, at()
#include<tuple> // for get()
#include <exception>
#include <algorithm>
using namespace std;
int main()
{
    // Initializing the array elements
    array<int,6> ar = {1, 2, 3, 4, 5, 6};

    // Printing array elements using at()
    cout << "The array elements are (using at()) : ";
    for ( int i=0; i<6; i++)
    cout << ar.at(i) << " ";
    cout << endl;

    // Printing array elements using get()
    cout << "The array elements are (using get()) : ";
    cout << get<0>(ar) << " " << get<1>(ar) << " ";
    cout << get<2>(ar) << " " << get<3>(ar) << " ";
    cout << get<4>(ar) << " " << get<5>(ar) << " ";
    cout << endl;

    // Printing array elements using operator[]
    cout << "The array elements are (using operator[]) : ";
    for ( int i=0; i<6; i++)
    cout << ar[i] << " ";
    cout << endl;

    try{
        cout<<ar.at(10)<<endl;
    }catch(exception &e)
    {
        cerr<<"Error: "<<e.what()<<endl;
    }

    array<int,6> ar1 = {6, 2, 3, 1, 4, 5};

    sort(ar1.begin(),ar1.end());

    for(int i=0;i<ar1.size();i++)
        cout<<ar1.at(i)<<" ";
    cout<<endl;

    cout<<ar1.back()<<endl;
    cout<<ar1.front()<<endl;
    ar1.fill(100);

    for(auto e: ar1)
        cout<<e<<" ";
    cout<<endl;

    cout<<"Size: "<<ar1.size()<<endl;
    cout<<"Max_Size: "<<ar1.max_size()<<endl;




    return 0;

}
