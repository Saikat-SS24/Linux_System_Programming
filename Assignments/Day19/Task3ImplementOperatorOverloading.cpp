/* 
Task 3: Implement Operator Overloading
Objective: Overload the + operator to add two Point objects.
Steps:
Define a Point class with x and y coordinates.
Overload the + operator to add two Point objects. */

#include <iostream>

using namespace std;

class Point {
private:
    int x, y;

public:
    // Constructor to initialize coordinates
    Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal) {}

    // Overloading the + operator
    // This function returns a new Point object
    Point operator+(const Point& other) {
        Point temp;
        temp.x = this->x + other.x; // Add x coordinates
        temp.y = this->y + other.y; // Add y coordinates
        return temp;
    }

    void display() {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Point p1(10, 5);
    Point p2(20, 15);

    // Using the overloaded + operator
    Point p3 = p1 + p2; 

    cout << "p1: "; p1.display();
    cout << "p2: "; p2.display();
    cout << "Result (p1 + p2): "; p3.display();

    return 0;
}