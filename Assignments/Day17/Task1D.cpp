/* Task 1D: Define a pointer initialized with string constant. Observe using gdb, the address where pointer is stored, the address contained the pointer where the string is stored. Observe are they in different areas of data storage classes (stack, data section etc.) */

#include <iostream>

using namespace std;

int main() {
    const char* strPtr = "Hello GDB";

    cout << "String literal value: " << strPtr << endl;
    cout << "Address of the pointer (on Stack): " << &strPtr << endl;
    cout << "Address stored in pointer (in Data Segment): " << (void*)strPtr << endl;

    return 0;
}

