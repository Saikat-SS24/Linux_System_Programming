/*Print array elements using only pointer arithmetic(no indexing)
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        // Using indexing only for input to keep it simple
        cin >> arr[i];
    }

    cout << "\nPrinting elements using Pointer Arithmetic:" << endl;

    // We start a pointer at the beginning of the array
    int* ptr = arr; 

    for (int i = 0; i < n; i++) {
        // 1. *(ptr + i) dereferences the address to get the value
        // 2. We are NOT using arr[i] here
        cout << "Element at index " << i << " is: " << *(ptr + i) << endl;
    }

    /* Alternative "Cooler" Way */
    cout << "\nPrinting by incrementing the pointer itself:" << endl;
    int* tempPtr = arr;
    for (int i = 0; i < n; i++) {
        cout << *tempPtr << " ";
        tempPtr++; // Move to the next memory location
    }

    return 0;
}