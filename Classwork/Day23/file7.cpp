#include <iostream>
#include <set>
using namespace std;

int main() {

    // Creating an empty set
    set<int> s1;

    // Initialize set with list 
    set<int> s2 = {1, 2, 3, 2, 1}; 

    // Traversing the set
    for (auto& x : s2)
        cout << x << " ";
    cout << endl;

    s1.insert(10);
    s1.insert(20);
    s1.insert(30);
    s1.insert(40);
    s1.insert(3);
    

    // Traversing the set
    for (auto& x : s1)
        cout << x << " ";
    cout << endl;

    
    auto it = s1.find(22);
    if(it != s1.end())
        cout<<"Found the element "<<*it<<endl;
    else 
        cout<<"\nNot Found"<<endl;
    
    if(s1.count(33))
        cout<<"Found"<<endl;
    else
        cout<<"not found"<<endl;

    return 0;
}