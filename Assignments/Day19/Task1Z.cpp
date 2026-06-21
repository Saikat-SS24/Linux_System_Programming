/* Task 1Z: Implement a Basic Class
Objective: Create a Car class with basic attributes.
Steps:
Define a Car class with private members: make, model, and year.
Write public member functions to set and get these values. */


#include <iostream>
#include <string>

class Car {
private:
    std::string make;
    std::string model;
    int year;

public:
    void setMake(std::string m) {
        make = m;
    }

    void setModel(std::string mod) {
        model = mod;
    }

    void setYear(int y) {
        if (y > 1885) { 
            year = y;
        } else {
            year = 0;
        }
    }

    std::string getMake() const {
        return make;
    }

    std::string getModel() const {
        return model;
    }

    int getYear() const {
        return year;
    }
};

int main() {
    Car myCar;

    myCar.setMake("BMW");
    myCar.setModel("BmwX");
    myCar.setYear(2026);

    std::cout << "Car Details:" << std::endl;
    std::cout << "Make:  " << myCar.getMake() << std::endl;
    std::cout << "Model: " << myCar.getModel() << std::endl;
    std::cout << "Year:  " << myCar.getYear() << std::endl;

    return 0;
}