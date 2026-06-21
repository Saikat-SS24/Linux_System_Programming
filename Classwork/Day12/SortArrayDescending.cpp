#include <iostream>
using namespace std;

// Function to sort an array in descending order
void sortDescending(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Check if the current element is smaller than the next
            if (arr[j] < arr[j + 1]) {
                // Swap them
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int data[] = {15, 3, 20, 8, 12};
    int n = 5;

    cout << "Original array: ";
    for (int i = 0; i < n; i++) cout << data[i] << " ";

    // Call the sorting function
    sortDescending(data, n);

    cout << "\nSorted (Descending): ";
    for (int i = 0; i < n; i++) cout << data[i] << " ";

    return 0;
}