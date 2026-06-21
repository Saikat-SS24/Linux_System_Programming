/*  
Functions
Task 1F: Observe the location of stack
Make two level function calls, with passing of parameters. Observe the address of the stack frames, where the local variables are stored and how the SP and BP registers are manipulated and how the return address is stored on the stack. */

#include <iostream>

void level2(int param2) {
    int local2 = param2 + 10;
    
    std::cout << "Inside Level 2: local2 = " << local2 << " at " << &local2 << std::endl;
}

void level1(int param1) {
    int local1 = param1 + 5;
    
    std::cout << "Inside Level 1: local1 = " << local1 << " at " << &local1 << std::endl;
    
    level2(local1); 
}

int main() {
    int startValue = 100;
    
    std::cout << "Starting Function Chain..." << std::endl;
    level1(startValue);
    
    return 0;
}