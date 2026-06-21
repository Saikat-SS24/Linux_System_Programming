/*Calculate factorial using loops*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    long long factorial = 1;

    cout << "Enter a positive number: ";
    cin >> n;

    if (n < 0)
    {
        cout << "Factorial of a negative number is not possible" << endl;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            factorial *= i;
        }
        
        cout << "Factorial of " << n << " = " << factorial << endl;
    }

    return 0;
}