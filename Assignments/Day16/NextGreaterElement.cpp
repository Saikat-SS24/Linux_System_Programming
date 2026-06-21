/*Given an array, find the next greater element for each element using stack

Example:

[4, 5, 2, 10] -> [5, 10, 10, 1]
*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);
    vector<int> nge(n, -1); // Initialize all answers as -1
    stack<int> s; // This stack will store "indexes"

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    for (int i = 0; i < n; i++) {
        // While stack is not empty AND current element is greater than the element 
        // at the index stored at the top of the stack
        while (!s.empty() && arr[i] > arr[s.top()]) {
            nge[s.top()] = arr[i]; // Current element is the NGE for the index on stack
            s.pop();               // They found their match, so remove from stack
        }
        
        // Push the current index onto the stack to find its NGE later
        s.push(i);
    }

    cout << "\nNext Greater Elements:\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " -> " << nge[i] << endl;
    }

    return 0;
}