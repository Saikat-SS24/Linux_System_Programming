#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
  
    // Creating an unordered_set of integers
    unordered_set<int> us = {10,1, 2, 3, 4, 5, 10};

    for (auto x : us) 
        cout << x << " ";
    return 0;
}