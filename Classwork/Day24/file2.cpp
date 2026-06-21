#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    auto it = lower_bound(v.begin(), v.end(), 29);

    cout << *it<<endl;

    auto it1 = upper_bound(v.begin(), v.end(), 33);

    cout << *it1<<endl;
    return 0;


    //char name[][]
}