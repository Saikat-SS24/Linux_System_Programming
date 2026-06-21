/*Given an array arr[] of positive integers of size N. 
Reverse every sub-array of K consecutive group of elements

TC_01
Input:
6
1 2 3 4 5 6
3

Output:
3 2 1 6 5 4 

TC_02
Input:
10
1 2 3 4 5 6 7 8 9 10
3

Output:
3 2 1 6 5 4 9 8 7 10

TC_03
Input:
6
1 2 1 5 5 6
3

Output:
1 2 1 6 5 5


TC_04
Input:
100
1 2 3 4 5 6
3

Output:
3 2 1 6 5 4   

TC_05
Input:
100
1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49 51 53 55 57 59 61 63 65 67 69 71 73 75 77 79 81 83 85 87 89 91 93 95 97 99 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46 48 50 52 54 56 58 60 62 64 66 68 70 72 74 76 78 80 82 84 86 88 90 92 94 96 98 100
3

output:

5 3 1 11 9 7 17 15 13 23 21 19 29 27 25 35 33 31 41 39 37 47 45 43 53 51 49 59 57 55 65 63 61 71 69 67 77 75 73 83 81 79 89 87 85 95 93 91 2 99 97 8 6 4 14 12 10 20 18 16 26 24 22 32 30 28 38 36 34 44 42 40 50 48 46 56 54 52 62 60 58 68 66 64 74 72 70 80 78 76 86 84 82 92 90 88 98 96 94 100

TC_06
Input:
10
HelloWorld
4

output:
l l e H r o W o d l
*/

#include <iostream>
#include <vector>
#include <algorithm> // Required for reverse()
using namespace std;

void reverseInGroups(vector<int>& arr, int n, int k) {
    for (int i = 0; i < n; i += k) {
        // Calculate the starting point
        int left = i;

        // Calculate the end point of the current group
        // Use min(i + k - 1, n - 1) to handle the last group 
        // if it has fewer than k elements
        int right = min(i + k - 1, n - 1);

        // Reverse the elements between left and right
        while (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
}

int main() {
    int n, k;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Enter group size (k): ";
    cin >> k;

    reverseInGroups(arr, n, k);

    cout << "Output: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}