#include <stdio.h>
#include <math.h>     // For sqrt()

// ─── JUMP SEARCH ─────────────────────────────────────────────────────
// Strategy: Divide and Conquer (block jumping + linear scan)
// Requires: SORTED array (ascending)
// Time:  O(√n) — better than O(n), worse than O(log n)
// Space: O(1)
// Best for: Large sorted arrays where binary search cache misses matter
//
// Returns: index of target if found, -1 if not found
int jumpSearch(int arr[], int size, int target) {
    // Step 1: Calculate optimal block size
    int step = (int)sqrt((double)size);   // √n
    int prev = 0;                         // Start of current block

    // Step 2: Jump forward until we overshoot or reach end
    printf("  Block size (√%d ≈ %d)\n", size, step);

    while (arr[(step < size ? step : size) - 1] < target) {
        printf("  Jump: arr[%d]=%d < %d → jump forward\n",
               (step < size ? step : size) - 1,
               arr[(step < size ? step : size) - 1],
               target);
        prev = step;
        step += (int)sqrt((double)size);

        if (prev >= size) return -1;   // Jumped past the end
    }

    printf("  Overshot at index %d → linear search from %d\n",
           (step < size ? step : size) - 1, prev);

    // Step 3: Linear search within the identified block
    while (arr[prev] < target) {
        printf("  Linear: arr[%d]=%d < %d → step forward\n",
               prev, arr[prev], target);
        prev++;
        if (prev == (step < size ? step : size)) return -1;
    }

    // Step 4: Check if we found the target
    if (arr[prev] == target) {
        printf("  Found at index %d!\n", prev);
        return prev;
    }

    return -1;
}

int main() {
    int sorted[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
    int n = sizeof(sorted) / sizeof(sorted[0]);

    printf("=== Jump Search Demo ===\n\n");
    printf("Array (%d elements): ", n);
    for (int i = 0; i < n; i++) printf("%d ", sorted[i]);
    printf("\n\n");

    printf("--- Searching for 55 ---\n");
    int result = jumpSearch(sorted, n, 55);
    printf("Result: %s\n\n", result != -1 ? "FOUND" : "NOT FOUND");

    printf("--- Searching for 100 ---\n");
    result = jumpSearch(sorted, n, 100);
    printf("Result: %s\n", result != -1 ? "FOUND" : "NOT FOUND");

    return 0;
}
