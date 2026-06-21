/*Given an array of positive integers, find if there exists a continuous subarray 
whose sum equals a target value.
*/


#include<iostream>
using namespace std;

int main()
{
    int n, target;
    cout << "Enter the size of the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter the target element: ";
    cin >> target;

    for (int i = 0; i < n; i++)
    {
        int currSum = 0;
        for (int j = i; j < n; j++)
        {
            currSum += arr[j];
            
            if (currSum == target)
            {
                cout << "subarray found between index " << i << " and " << j << endl;
                return 0;
            }
            if (currSum > target)
            {
                break;
            }
        }
        
    }
}