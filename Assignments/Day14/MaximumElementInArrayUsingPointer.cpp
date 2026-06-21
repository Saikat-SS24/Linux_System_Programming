/* Write a function that takes a pointer to an array and returns the maximum element */

#include <iostream>
using namespace std;

// Function takes a pointer to the first element and the size of the array
int findMax(int* ptr, int size) {
    // 1. Assume the first element is the maximum
    int maxVal = *ptr; 

    // 2. Loop through the rest of the elements
    for (int i = 1; i < size; i++) {
        // *(ptr + i) accesses the value at the i-th position
        if (*(ptr + i) > maxVal) {
            maxVal = *(ptr + i);
        }
    }

    return maxVal;
}

int main() {
    int arr[] = {15, 42, 7, 89, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Pass the array (which acts as a pointer to the first element)
    int result = findMax(arr, n);

    cout << "The maximum element is: " << result << endl;

    return 0;
}