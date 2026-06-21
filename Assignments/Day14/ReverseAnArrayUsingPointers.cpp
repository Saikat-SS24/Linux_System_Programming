/*Reverse an array using pointers (no indexing allowed)*/

#include <iostream>
using namespace std;

void reverseArray(int* start, int* end) {
    // While the two pointers haven't met or crossed
    while (start < end) {
        // Swap the values at the pointers without a temp variable (using math)
        *start = *start + *end;
        *end = *start - *end;
        *start = *start - *end;

        // Move the start pointer forward and end pointer backward
        start++;
        end--;
    }
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    // Pointer to first element and pointer to last element
    reverseArray(arr, arr + n - 1);

    cout << "Reversed Array: ";
    for (int i = 0; i < n; i++) {
        cout << *(arr + i) << " "; // Printing using pointer arithmetic
    }
    cout << endl;

    return 0;
}