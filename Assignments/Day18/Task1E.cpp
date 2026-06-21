/* Task 1E: Operation with double pointers. Learn to modify the data using a double pointer. */

#include <iostream>
using namespace std;

int main() {
    int val = 500;
    int* ptr = &val;      // Pointer to val
    int** dptr = &ptr;    // Double pointer to ptr

    cout << "Value using val: " << val << endl;
    cout << "Value using *ptr: " << *ptr << endl;
    cout << "Value using **dptr: " << **dptr << endl;

    // Modifying data using double pointer
    **dptr = 1000;
    cout << "Modified value: " << val << endl;

    return 0;
}