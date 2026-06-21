/*Write the logic to print inverted right triangle star pattern.

Input Format  : First line contains N of type integer.

Output Format : Print the inverted right triangle star pattern.

Constrains:
2<=N<=10
Sample Input:
5

Sample Output:
*****
****
***
**
*
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    for (int i = n; i >= 1; i--) {

        for (int j = 1; j <= i; j++) {
            cout << "*";
        }

        // Move to the next line after each row
        cout << endl;
    }

    return 0;
}