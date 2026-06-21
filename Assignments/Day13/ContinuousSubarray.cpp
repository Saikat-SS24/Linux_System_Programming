/*Problem Statement:
Given an unsorted array a of size N of non-negative integers, 
find a continuous sub-array which adds to a given number sum.

Input Format:
The first line contains an integer, denoting the size of the array. 
The second line contains integers denoting the elements 
of the array.
The last line contains an integer, denoting the sum. 

Constraints
1<= n<=100
1<=arr<= 1000, where arr is the ith element of the array.
1<= n<=100000

Output Format:
The output line contains integers denoting the indexes.

TESTCASE 1:
Input:
7
[1, 4, 0, 0, 3, 10, 5]

sum = 7
Output: 
Sum found between indexes 1 and 4

TESTCASE 2:
Input:
2
[1, 4]
sum = 0
Output: 
No subarray found
*/

#include<iostream>
using namespace std;

int main()
{
    int n, target;
    cout << "Enter the array size: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter the target element: ";
    cin >> target;

    int left= 0,right = 0, currSum = 0;
    while (right < n)
    {
        currSum += arr[right];
        while(currSum > target && left < right)
        {
            currSum -= arr[left];
            left++;
        }
        if (currSum == target)
        {
            cout << "sum found from index: " << left << " to " << right << endl;
            return 0;
        }

        right++;

    }

    cout << "NO subarray found." << endl;
    return 0;
}