/* 
Tasl 10: Templates with Functions
Objective: Write a function template to compare two values.
Steps:
Define a template function compare that returns the larger of two values.
Instantiate and test the function with int, float, and string types. */


#include <iostream>
#include <string>
using namespace std;

template <typename T>
T compareMax(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int i1 = 10, i2 = 20;
    cout << "Max of " << i1 << " and " << i2 << " is: " << compareMax(i1, i2) << endl;

    float f1 = 5.55, f2 = 5.56;
    cout << "Max of " << f1 << " and " << f2 << " is: " << compareMax(f1, f2) << endl;

    string s1 = "Apple", s2 = "Zebra";
    cout << "Max of " << s1 << " and " << s2 << " is: " << compareMax(s1, s2) << endl;

    return 0;
}