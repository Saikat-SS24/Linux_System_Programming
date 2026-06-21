/* Task 2: Utilize Constructors and Destructors	
Objective: Understand the use of constructors and destructors.	
Steps:	
Add a constructor to the Car class to initialize all attributes.	
Implement a destructor that prints a message when an object is destroyed.	*/

#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string make;
    string model;
    int year;

public:
    Car(string m, string mod, int y) : make(m), model(mod), year(y) {
        cout << "--- Constructor: Creating " << make << " " << model << " ---" << endl;
    }

    ~Car() {
        cout << "--- Destructor: Destroying " << make << " " << model << " ---" << endl;
    }

    void display() {
        cout << "Car Info: " << year << " " << make << " " << model << endl;
    }
};

int main() {
    cout << "Start of main()" << endl;

    {
        cout << "  Entering inner scope..." << endl;
        
        Car myCar("BMW", "BmwX", 2026);
        myCar.display();

        cout << "  Exiting inner scope..." << endl;
    } 

    cout << "End of main()" << endl;
    return 0;
}

