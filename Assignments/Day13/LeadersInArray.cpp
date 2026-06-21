/*Given an array of positive integers. 
Your task is to find the leaders in the array. An element is leader if it is greater than all the elements to its right side.
And the rightmost element is always a leader.

Input Format:
The first line contains an integer, denoting the size of the array. 
The second line contains integers denoting the elements of the array.
 
Constraints
 1<= n<=100-1000<=arr[i]<= 1000, where arr is the ith  element of the array.
 Output Format:
 The output line prints all the leaders in the array.
 
TESTCASE 1:
 Input:
 6
 6 7 4 3 5 2
 Output: 
 2 5 7
 
TESTCASE 2:
 Input:
 5
 2 6 3 8 4 
 Output:
 4 8
*/
#include <iostream>
#include <vector>
#include <algorithm> // Required for reverse()
using namespace std;

void findLeaders(int arr[], int n) {
    // 1. Rightmost element is always a leader
    int current_max = arr[n - 1];
    vector<int> leaders;
    
    leaders.push_back(current_max);

    // 2. Scan the array from right to left
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] > current_max) {
            current_max = arr[i];
            leaders.push_back(current_max);
        }
    }

    // 3. Since we scanned right-to-left, the leaders are in reverse order.
    // Let's print them out (or reverse the vector)
    cout << "Leaders: ";
    for (int i = leaders.size() - 1; i >= 0; i--) {
        cout << leaders[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    findLeaders(arr, n);

    return 0;
}