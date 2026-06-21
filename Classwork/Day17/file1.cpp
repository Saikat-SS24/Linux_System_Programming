#include <iostream>

using namespace std;

// ─── LINEAR SEARCH ────────────────────────────────────────────────────
// Strategy: Brute Force — check each element sequentially
// Works on: Sorted AND unsorted arrays
// Time:  O(n) worst case, O(1) best case
// Space: O(1) — no extra memory needed
//
// Returns: index of target if found, -1 if not found
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;    // Target found at index i
        }
    }
    return -1;           // Target not in array
}

// ─── FIND ALL OCCURRENCES ─────────────────────────────────────────────
// Enhanced version: prints ALL positions where target appears
void linearSearchAll(int arr[], int size, int target) {
    int found = 0;
    printf("Searching for %d...\n", target);

    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            printf("  Found at index: %d\n", i);
            found++;
        }
    }

    if (found == 0)
        printf("  Not found.\n");
    else
        printf("  Total occurrences: %d\n", found);
}



int main() {
    int data[] = {64, 25, 12, 22, 11, 90, 5, 42, 33};
    int n = sizeof(data) / sizeof(data[0]);

    printf("=== Linear Search Demo ===\n\n");
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", data[i]);
    printf("\n\n");

    // Search 1: found
    int idx = linearSearch(data, n, 22);
    printf("Search for 22: %s\n",
           idx != -1 ? "Found" : "Not Found");
    if (idx != -1) printf("  → Index: %d\n", idx);

    // Search 2: not found
    idx = linearSearch(data, n, 100);
    printf("Search for 100: %s\n\n",
           idx != -1 ? "Found" : "Not Found");

    // Find all occurrences
    int data2[] = {3, 7, 3, 9, 3, 1, 3};
    int n2 = 7;
    printf("Array with duplicates: ");
    for (int i = 0; i < n2; i++) printf("%d ", data2[i]);
    printf("\n");
    linearSearchAll(data2, n2, 3);

    return 0;
}
