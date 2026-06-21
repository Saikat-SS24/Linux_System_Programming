/* Data types
Task 1A: Observe layout of data in memory using gdb
Define variables of differnt types initialized with predefined data. The variables should be local variables, global variables, static variables, constants. Put a break point in gdb on main function and observe the memory layout of the variables in memory. Understand stack and heap memory areas.*/

#include <iostream>

int globalVar = 100;

static int staticVar = 200;

const int constantVar = 300;

int main() {
    int localVar = 10;

    const int localConst = 20;

    int* heapVar = new int(500);

    std::cout << "Variables initialized. Check GDB now." << std::endl;

    delete heapVar; 
    return 0;
}