#include <iostream>
using namespace std;

// ─── BINARY SEARCH (ITERATIVE) ───────────────────────────────────────
// Strategy: Divide and Conquer
// Requires: SORTED array (ascending order)
// Time:  O(log n) — halves the search space each iteration
// Space: O(1) — no recursion stack needed
//
// Returns: index of target if found, -1 if not found
int binarySearchIterative(int arr[], int size, int target) {
    int low  = 0;           // Left boundary of search window
    int high = size - 1;    // Right boundary of search window

    while (low <= high) {
        // IMPORTANT: Use (low + high)/2 carefully to avoid integer overflow
        // Safe formula: mid = low + (high - low) / 2
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;              // ✓ Found!

        } else if (arr[mid] < target) {
            low = mid + 1;           // Target is in RIGHT half

        } else {
            high = mid - 1;          // Target is in LEFT half
        }
    }

    return -1;    // Not found
}

// ─── BINARY SEARCH (RECURSIVE) ───────────────────────────────────────
// Same logic but expressed recursively — elegant and intuitive
// Time:  O(log n)
// Space: O(log n) — recursion stack depth
int binarySearchRecursive(int arr[], int low, int high, int target) {
    // Base case: search window is empty
    if (low > high) return -1;

    int mid = low + (high - low) / 2;

    if (arr[mid] == target)
        return mid;                                    // Found!

    if (arr[mid] < target)
        return binarySearchRecursive(arr, mid + 1, high, target); // Search right

    return binarySearchRecursive(arr, low, mid - 1, target);      // Search left
}

// ─── FIND FIRST OCCURRENCE (for duplicate elements) ──────────────────
// Standard binary search finds ANY occurrence of duplicates.
// This version finds the FIRST (leftmost) occurrence.
int findFirst(int arr[], int size, int target) {
    int low = 0, high = size - 1, result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid;         // Record this position
            high = mid - 1;       // But keep searching LEFT for earlier one
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// ─── STEP-BY-STEP TRACE ──────────────────────────────────────────────
// Educational version: shows every step of the algorithm
int binarySearchVerbose(int arr[], int size, int target) {
    int low = 0, high = size - 1, step = 1;

    printf("Searching for %d in array of %d elements:\n", target, size);

    while (low <= high) {
        int mid = low + (high - low) / 2;
        printf("  Step %d: low=%d, high=%d, mid=%d → arr[%d]=%d ",
               step++, low, high, mid, mid, arr[mid]);

        if (arr[mid] == target) {
            printf("→ MATCH! Found at index %d\n", mid);
            return mid;
        } else if (arr[mid] < target) {
            printf("→ Too small, search RIGHT\n");
            low = mid + 1;
        } else {
            printf("→ Too large, search LEFT\n");
            high = mid - 1;
        }
    }
    printf("  Target not found.\n");
    return -1;
}

int main() {
    int sorted[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int n = sizeof(sorted) / sizeof(sorted[0]);

    printf("=== Binary Search Demo ===\n\n");
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", sorted[i]);
    printf("\n\n");

    // Iterative search
    printf("--- Iterative Binary Search ---\n");
    int idx = binarySearchIterative(sorted, n, 38);
    printf("Search for 38: %s (index %d)\n\n",
           idx != -1 ? "FOUND" : "NOT FOUND", idx);

    // Recursive search
    printf("--- Recursive Binary Search ---\n");
    idx = binarySearchRecursive(sorted, 0, n - 1, 5);
    printf("Search for 5:  %s (index %d)\n\n",
           idx != -1 ? "FOUND" : "NOT FOUND", idx);

    // Verbose trace
    printf("--- Step-by-step trace ---\n");
    binarySearchVerbose(sorted, n, 56);
    printf("\n");
    binarySearchVerbose(sorted, n, 100);

    // First occurrence
    int withDups[] = {1, 2, 3, 3, 3, 4, 5};
    printf("\n--- First Occurrence (duplicates) ---\n");
    printf("Array: 1 2 3 3 3 4 5\n");
    printf("First '3' at index: %d\n", findFirst(withDups, 7, 3));

    return 0;
}
