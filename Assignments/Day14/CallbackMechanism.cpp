/* Write a function that accepts another function as argument and applies it on array elements */

#include <iostream>
using namespace std;

// 1. Define some "logic" functions
void square(int &n) {
    n = n * n;
}

void doubleVal(int &n) {
    n = n * 2;
}

// 2. Define the "Engine" function
// It accepts: a pointer to an array, the size, and a function pointer
void applyToArray(int arr[], int size, void (*func)(int &)) {
    for (int i = 0; i < size; i++) {
        func(arr[i]); // Apply the passed function to the current element
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";

    // Pass the 'doubleVal' function as an argument
    applyToArray(arr, n, doubleVal);

    cout << "\nAfter Doubling: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";

    // Pass the 'square' function as an argument
    applyToArray(arr, n, square);

    cout << "\nAfter Squaring: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}