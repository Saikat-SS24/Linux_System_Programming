/*Count frequency of elements in an array without 
using another array or map.
*/

#include<iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    
    int arr[n];
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int visited = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == visited)
        {
            continue;
        }

        int count = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
                visited = arr[j];
            }
        }

        cout << "Element " << arr[i] << " appears " << count << " times" << endl;
    }
    
    return 0;
}