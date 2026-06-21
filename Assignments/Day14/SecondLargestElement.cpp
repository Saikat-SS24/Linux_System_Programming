/*Write a program to find the second largest element in an array without sorting it.
Handle duplicates properly
*/

#include<iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    if (n < 2)
    {
        cout << "Array should have atleast two elements: ";
        return 0;
    }
    int arr[n];
    cout << "Enter: " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int largest = -1, secondLarrgest = -1;

    for (int i = 0; i < n; i++)
        if (arr[i] > largest)
        {
            largest = arr[i];
        }
    
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > secondLarrgest && arr[i] != largest)
        {
            secondLarrgest = arr[i];
        }
    }

    cout << "The second largest elements is: " << secondLarrgest << endl;
    
}