#include <iostream>
#include <list>
using namespace std;

int main(){
    list<int> l = {1, 3, 4, 2, 5};

    l.pop_back();
    l.pop_front();
    
    auto it = l.begin();
    advance(it, 2);
    l.erase(it);

    for (auto i : l)
        cout << i << " ";
    
    l.clear();
    cout<<"Size: "<<l.size()<<endl;
    return 0;
}