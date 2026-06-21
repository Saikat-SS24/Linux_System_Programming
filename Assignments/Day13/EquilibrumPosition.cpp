/*Given an array A of N positive numbers. The task is to find the position 
where equilibrium first occurs in the array. Equilibrium position in an array is a position such that the sum of elements before it is equal to the sum of   elements after it.

Input Format:
The first line contains an integer, denoting the size of the array. 
The second line contains integers denoting the elements 
of the array.
Constraints
1<= n<=100
1<=arr<= 1000, where arr is the ith element of the array.

Output Format:
The output line contains integer denoting an equilibrium
index (if any) or -1 (if no equilibrium indexes exist).

TESTCASE 1:
Input:
7
[-7, 1, 5, 2, -4, 3, 0]

o/p
3

I/p
5
[0 0 0 0 -1]

o/p
4
*/

#include <iostream>
using namespace std;

int findEquilibrium(int arr[], int n) {
    int totalSum = 0;
    int leftSum = 0;

    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
    }

    for (int i = 0; i < n; i++) {
        // Right sum is (Total - LeftSum - CurrentElement)
        int rightSum = totalSum - leftSum - arr[i];

        if (leftSum == rightSum) {
            return i; // Found the equilibrium index!
        }

        // Add current element to leftSum for the next iteration
        leftSum += arr[i];
    }

    return -1; // No equilibrium point found
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int result = findEquilibrium(arr, n);

    if (result != -1) {
        cout << "Equilibrium position found at index: " << result << endl;
    } else {
        cout << "No equilibrium position found." << endl;
    }

    return 0;
}