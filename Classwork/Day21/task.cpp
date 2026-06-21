#include<iostream>
using namespace std;

class Vehicle{
public: 
    void move(){
        cout << "The vehicle is running on the road" << endl;
    }
};

class Engine {
public:
    int horesepower;
    Engine() {horesepower = 150; }
    void start() { cout << "Engine makes sound at " << horesepower << "HP." << endl; }
};

class Passenger{
public:
    string name;
    Passenger() {name = "None"; }
    void setName(string n) {name = n;}
};

class Car: public Vehicle{
public: 
    Engine myEngine;
    Passenger myPassenger;
    void drive(){
        cout << "Driver " << myPassenger.name << "is ready." << endl;
        myEngine.start();
        move();
    }
};

int main(){
    Passenger person;
    person.setName("Bob");
    cout << "==========Creating a Car===========" << endl;
    {
        Car myCar;
        myCar.myPassenger = person;
        myCar.drive();
    }
    // myCar and it's engine are destroyed here
    cout << "\n==== Outside the Car's life======" << endl;
    cout << "Passenger " << person.name << " is still alive and well" << endl;

    return 0;
}