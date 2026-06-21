/* 
Task 15: Using the auto Keyword
Objective: Practice the use of auto to simplify code.
Steps:
Declare a few variables with auto, initializing them with different types.
Print the types of the variables using typeid().name().*/

#include <iostream>
#include <typeinfo> // Required for typeid().name()
#include <vector>
#include <string>

using namespace std;

int main() {
    auto integerVar = 100;              // Deduces int
    auto doubleVar = 3.1415;            // Deduces double
    auto stringVar = string("Saikat");  // Deduces std::string
    auto charVar = 'T';                 // Deduces char
    auto boolVar = true;                // Deduces bool

    cout << "Value: " << integerVar << " | Type: " << typeid(integerVar).name() << endl;
    cout << "Value: " << doubleVar  << " | Type: " << typeid(doubleVar).name() << endl;
    cout << "Value: " << stringVar  << " | Type: " << typeid(stringVar).name() << endl;
    cout << "Value: " << charVar    << " | Type: " << typeid(charVar).name() << endl;
    cout << "Value: " << boolVar    << " | Type: " << typeid(boolVar).name() << endl;

    vector<string> names = {"Alice", "Bob"};
    auto it = names.begin(); // Deduce vector<string>::iterator
    cout << "Iterator Type: " << typeid(it).name() << endl;

    return 0;
}