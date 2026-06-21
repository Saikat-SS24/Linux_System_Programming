/* Rotate an array to the right by k positions without using extra memory */

#include <iostream>
using namespace std;

// Basic function to reverse a portion of the array using pointers
void reverse(int* start, int* end) {
    while (start < end) {
        // Swap values using a temp variable
        int temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

void rotateRight(int arr[], int n, int k) {
    // Handle cases where k > n
    k = k % n;
    if (k == 0) return;

    // Step 1: Reverse the whole array
    reverse(arr, arr + n - 1);

    // Step 2: Reverse the first k elements
    reverse(arr, arr + k - 1);

    // Step 3: Reverse the rest
    reverse(arr + k, arr + n - 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    int k = 2;

    cout << "Original: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    
    rotateRight(arr, n, k);

    cout << "\nRotated by " << k << ": ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}