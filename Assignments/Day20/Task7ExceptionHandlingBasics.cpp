/* 
Task 7: Exception Handling Basics
Objective: Handle exceptions in a function that divides two numbers.
Steps:
Write a function that takes two integers and divides them.
Use try-catch blocks to handle division by zero.*/

#include <iostream>
#include <stdexcept> // Required for runtime_error

using namespace std;

// Function to perform division
double divide(int a, int b) {
    if (b == 0) {
        throw runtime_error("Math Error: Division by zero is not allowed!");
    }
    return (double)a / b;
}

int main() {
    int num1, num2;

    cout << "Enter numerator: ";
    cin >> num1;
    cout << "Enter denominator: ";
    cin >> num2;

    try {
        double result = divide(num1, num2);
        cout << "Result: " << result << endl;
    } 
    catch (const runtime_error& e) {
        cout << "Caught an exception: " << e.what() << endl;
    }

    cout << "Program continues running..." << endl;

    return 0;
}