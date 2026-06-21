/* Write a function that takes an array and: 
Replaces even numbers with 0
Double odd numbers */

#include <iostream>
using namespace std;

// Function to process the array
void processArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        // Check if the number is even
        if (arr[i] % 2 == 0) {
            arr[i] = 0; // Replace even with 0
        } 
        // Otherwise, it must be odd
        else {
            arr[i] = arr[i] * 2; // Double the odd number
        }
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(nums) / sizeof(nums[0]);

    cout << "Before: ";
    for (int i = 0; i < n; i++) cout << nums[i] << " ";

    processArray(nums, n);

    cout << "\nAfter:  ";
    for (int i = 0; i < n; i++) cout << nums[i] << " ";
    cout << endl;

    return 0;
}