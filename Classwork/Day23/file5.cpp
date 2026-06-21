#include <bits/stdc++.h>
using namespace std;

int main() {
    forward_list<int> fl = {1, 5, 3, 4};


    fl.push_front(10);

    // Access the first element
    cout << fl.front() << endl;
    fl.insert_after(fl.begin(),30);
    
    // Access third element
    auto it = next(fl.begin(), 2);
    cout << *it;
    cout<<endl;
    for(auto i: fl)
        cout<<i<<" ";
    cout<<endl;

    auto it1 = fl.begin();
    for(auto i: fl)
    {
        if (i==5)
            break;
        ++it1;
    }

    fl.insert_after(it1, 200);
    cout<<endl;
    for(auto i: fl)
        cout<<i<<" ";
    cout<<endl;

    
    return 0;
}