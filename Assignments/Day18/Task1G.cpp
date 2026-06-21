/* Task 1G: Define function pointer and use a function pointer
Define a function operation() which should take a function pointer and 2 more arguments. Define add, subtrack, multiply and divide as functions. Pass one of these functions to operation() with other  two arguments and check correct function gets called. */

#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { 
    if (b == 0) return 0; 
    return a / b; 
}

/*The operation function
  - callback: a function pointer that takes two ints and returns an int
  - x, y: the arguments to be passed to the callback */
  
void operation(int (*callback)(int, int), int x, int y) {
    int result = callback(x, y);
    cout << "The result of the operation is: " << result << endl;
}

int main() {
    int num1 = 20, num2 = 10;

    cout << "Calling ADD via operation():" << endl;
    operation(add, num1, num2);

    cout << "\nCalling SUBTRACT via operation():" << endl;
    operation(subtract, num1, num2);

    cout << "\nCalling MULTIPLY via operation():" << endl;
    operation(multiply, num1, num2);

    return 0;
}