/* Sort an array using a function pointer to choose Ascending, Descending */

#include <iostream>
using namespace std;

// 1. Comparison logic for Ascending
bool compareAsc(int a, int b) {
    return a > b; // Returns true if elements need to be swapped
}

// 2. Comparison logic for Descending
bool compareDesc(int a, int b) {
    return a < b; // Returns true if elements need to be swapped
}

// 3. Generic Bubble Sort that takes a function pointer
// The pointer 'compare' points to either compareAsc or compareDesc
void bubbleSort(int arr[], int n, bool (*compare)(int, int)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Use the function pointer to decide if we should swap
            if (compare(arr[j], arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int choice;

    cout << "Array: 5, 2, 9, 1, 5, 6" << endl;
    cout << "1. Sort Ascending\n2. Sort Descending\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        bubbleSort(arr, n, compareAsc);
    } else {
        bubbleSort(arr, n, compareDesc);
    }

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}