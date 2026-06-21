#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isOdd(int i) { 
    return i%2; 
}

int main() {
    vector<int> v = {1, 3, 6, 2, 9};

    // Sorting the vector
    //sort(v.begin(), v.end());

    // Search for element 6
    auto it = find(v.begin(), v.end(), 6);

    // Print index
    if(it != v.end())
        cout << distance(v.begin(), it)<<endl;
    else
        cout<<"Not Found"<<endl;

    vector<int>:: iterator it1;

    //it1 = find_if(v.begin(), v.end(), [](int i){ return i%2;});
    it1 = find_if(v.begin(), v.end(), isOdd);

   cout<<*it1<<endl; 
    return 0;
}