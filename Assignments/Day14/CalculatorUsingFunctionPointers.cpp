/* Implement a calculator using function pointers for " + - * /" */

#include <iostream>
using namespace std;

// 1. Define basic math functions
float add(float a, float b) { return a + b; }
float subtract(float a, float b) { return a - b; }
float multiply(float a, float b) { return a * b; }
float divide(float a, float b) { 
    if (b == 0) {
        cout << "Error: Division by zero!" << endl;
        return 0;
    }
    return a / b; 
}

int main() {
    float num1, num2;
    int choice;

    // 2. Declare a function pointer
    // Syntax: return_type (*pointer_name)(parameter_types)
    float (*funcPtr)(float, float);

    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    cout << "\nChoose Operation:\n1. Add (+)\n2. Subtract (-)\n3. Multiply (*)\n4. Divide (/)\nEnter choice (1-4): ";
    cin >> choice;

    // 3. Assign the function address to the pointer based on choice
    switch (choice) {
        case 1: funcPtr = add; break;
        case 2: funcPtr = subtract; break;
        case 3: funcPtr = multiply; break;
        case 4: funcPtr = divide; break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    // 4. Call the function through the pointer
    cout << "Result: " << funcPtr(num1, num2) << endl;

    return 0;
}