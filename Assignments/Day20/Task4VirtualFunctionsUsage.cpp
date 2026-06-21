/* 
Task 4: Virtual Functions Usage
Objective: Demonstrate polymorphism with virtual functions.
Steps:
Create a base class Shape with a virtual function draw().
Derive Circle and Square classes and override draw().*/

#include <iostream>

using namespace std;

// Base Class
class Shape {
public:
    // The 'virtual' keyword enables dynamic linkage
    virtual void draw() {
        cout << "Drawing a generic Shape" << endl;
    }

    virtual ~Shape() {}
};

// Derived Class 1
class Circle : public Shape {
public:
    // 'override' keyword ensures overriding a base function
    void draw() override {
        cout << "Drawing a Circle (O)" << endl;
    }
};

// Derived Class 2
class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing a Square [ ]" << endl;
    }
};

int main() {
    // 1. Using Base Pointers to achieve Polymorphism
    Shape* shape1 = new Circle();
    Shape* shape2 = new Square();

    cout << "Calling draw() through Base Class pointers:" << endl;
    
    shape1->draw(); // Prints: Drawing a Circle
    shape2->draw(); // Prints: Drawing a Square

    // Cleanup
    delete shape1;
    delete shape2;

    return 0;
}