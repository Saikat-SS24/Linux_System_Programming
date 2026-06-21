/* 
Task 13: Lambda Expressions
Objective: Write a lambda expression to sort a vector<string>.
Steps:
Create a vector<string> with some unsorted names.
Use std::sort with a lambda to sort the names in descending order.*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<string> names = {"Diana", "Alice", "Edward", "Charlie", "Bob"};

    cout << "Original: ";
    for (const string& n : names) cout << n << " ";
    cout << endl;

    sort(names.begin(), names.end(), [](string a, string b) {
        return a > b; // Returns true if 'a' should come before 'b'
    });

    cout << "Descending (Lambda): ";
    for (const string& n : names) cout << n << " ";
    cout << endl;

    return 0;
}