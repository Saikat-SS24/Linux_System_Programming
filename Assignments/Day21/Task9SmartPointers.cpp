/* 
Task 9: Smart Pointers
Objective: Illustrate the use of std::unique_ptr.
Steps:
Create a std::unique_ptr to a new Car object.
Use the unique_ptr to access Car member functions. */

#include <iostream>
#include <memory> // Required for smart pointers
#include <string>

using namespace std;

class Car {
public:
    string model;
    
    Car(string m) : model(m) {
        cout << "Car " << model << " created." << endl;
    }

    ~Car() {
        cout << "Car " << model << " destroyed automatically!" << endl;
    }

    void drive() {
        cout << "The " << model << " is driving." << endl;
    }
};

int main() {
    cout << "--- Start of Main ---" << endl;

    {
        unique_ptr<Car> myCar = make_unique<Car>("Tesla Model S");

        myCar->drive();

        cout << "Still inside the scope..." << endl;
    } 

    cout << "--- End of Main ---" << endl;

    return 0;
}