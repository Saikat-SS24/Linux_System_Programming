#include <iostream>
#include <map>
using namespace std;

int main() {
    
    // Creating an empty map
    map<int, string> m1;

    // Initialze map with list
    map<int, string> m2 = {{1, "Geeks"},
              {2, "For"}, {1, "Geeks"}};

    for (auto& p : m2)
        cout << p.first << " " <<
        p.second << endl;
    return 0;
}