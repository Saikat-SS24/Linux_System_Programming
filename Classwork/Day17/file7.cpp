#include <stdio.h>

void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// ─── PARTITION ───────────────────────────────────────────────────────
// Places pivot in its correct sorted position.
// Everything left of pivot < pivot, everything right > pivot.
// Returns: the final index of the pivot
int partition(int arr[], int low, int high) {
    //int pivot = arr[high];   // Choose last element as pivot
    int mid = low + (high-low)/2;
    int pivot = arr[mid];
    int i = low - 1;         // i tracks where to place next "small" element

    printf("  Partitioning [%d..%d], pivot=%d\n", low, high, pivot);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Place pivot in its correct position
    swap(&arr[i + 1], &arr[high]);

    printf("  After partition: ");
    printArray(arr, high + 2 > 10 ? 10 : high + 2);   // show subset

    return i + 1;   // Return pivot's final index
}

// ─── QUICK SORT ──────────────────────────────────────────────────────
// Strategy: Divide and Conquer — partition around pivot, recurse
// Time:  O(n log n) average, O(n²) worst (sorted input with bad pivot)
// Space: O(log n) recursion stack
// Stable: NO (swaps can change equal elements' order)
//
// Tip: Use randomized pivot or median-of-three to avoid worst case
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition and get pivot's final position
        int pivotIndex = partition(arr, low, high);

        // Recursively sort left and right of pivot
        quickSort(arr, low, pivotIndex - 1);   // Left sub-array
        quickSort(arr, pivotIndex + 1, high);  // Right sub-array
    }
}

// ─── RANDOMIZED QUICK SORT (BETTER PIVOT) ────────────────────────────
// Avoids worst-case O(n²) on sorted/reverse-sorted inputs
#include <stdlib.h>
#include <time.h>

int partitionRandom(int arr[], int low, int high) {
    // Randomly pick a pivot and swap to end
    int randIdx = low + rand() % (high - low + 1);
    swap(&arr[randIdx], &arr[high]);
    return partition(arr, low, high);
}

void quickSortRandom(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRandom(arr, low, high);
        quickSortRandom(arr, low, pivotIndex - 1);
        quickSortRandom(arr, pivotIndex + 1, high);
    }
}

int main() {
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Quick Sort Demo ===\n\n");
    printf("Before: "); printArray(arr, n);
    printf("\nPartition trace:\n");
    quickSort(arr, 0, n - 1);
    printf("\nAfter:  "); printArray(arr, n);

    return 0;
}