/*Write the logic to print star pattern or rectangle star pattern.

Input Format  : First line contains N of type integer.

Output Format : Print the rectangle star pattern.

Constrains:
2<=N<=10

Sample Input:
5

Sample Output:
*****
*****
*****
*****
*****
*/

#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter the size: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
