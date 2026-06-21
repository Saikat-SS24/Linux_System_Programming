/* 
Task 5: Abstract Class and Pure Virtual Functions
Objective: Define an abstract class with a pure virtual function.
Steps:
Modify the Shape class to make draw() a pure virtual function.
Ensure derived classes implement the draw() function.*/

#include <iostream>

using namespace std;

// --- Abstract Base Class ---
class Shape {
public:
    virtual void draw() = 0;

    virtual ~Shape() {}
};

// --- Derived Class 1 ---
class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing a Circle (O)" << endl;
    }
};

// --- Derived Class 2 ---
class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing a Square [ ]" << endl;
    }
};

int main() {
    Shape* s1 = new Circle();
    Shape* s2 = new Square();

    s1->draw();
    s2->draw();

    // Cleanup
    delete s1;
    delete s2;

    return 0;
}