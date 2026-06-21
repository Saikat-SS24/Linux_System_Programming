#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// ─── MERGE ───────────────────────────────────────────────────────────
// Merges two sorted sub-arrays: arr[left..mid] and arr[mid+1..right]
// Uses a temporary array to hold merged result, then copies back
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;       // Size of left sub-array
    int n2 = right - mid;           // Size of right sub-array

    // Allocate temporary arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data into temp arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    printf("  Merging [");
    for (int i = 0; i < n1; i++) printf("%d%s", L[i], i<n1-1?",":"");
    printf("] + [");
    for (int j = 0; j < n2; j++) printf("%d%s", R[j], j<n2-1?",":"");
    printf("] → ");

    // Merge back into arr
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {        // <= makes it STABLE
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copy remaining elements (one of these will do nothing)
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // Print result
    for (int x = left; x <= right; x++) printf("%d ", arr[x]);
    printf("\n");

    free(L);
    free(R);
}

// ─── MERGE SORT ──────────────────────────────────────────────────────
// Strategy: Divide and Conquer — split, recurse, merge
// Time:  O(n log n) — guaranteed, even worst case
// Space: O(n) — temporary arrays during merge
// Stable: YES — equal elements maintain relative order
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;   // Avoid overflow

        // Recursively sort left and right halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Merge Sort Demo ===\n\n");
    printf("Before: "); printArray(arr, n);
    printf("\nMerge trace:\n");
    mergeSort(arr, 0, n - 1);
    printf("\nAfter:  "); printArray(arr, n);

    return 0;
}
