/*write a program to read Sum and Product of digits in a given number

Input Format:
Read a positive integer N

Output Format:
Print the sum and product of digits of the number

Examples:
Input: N = 12
Output: 
sum =3 
product = 2.

Input: N = 1012
Output:
 Sum = 4 
product = 2 */

#include<iostream>
using namespace std;

int main()
{
    int num, digit;
    int sum = 0;
    int prod = 1;
    cout << "Enter the number: ";
    cin >> num;

    while (num > 0)
    {
        digit = num%10;
        sum = sum + digit;
        prod = prod * digit;
        num = num / 10;
    }

    cout << "Sum = " << sum << endl;
    cout << "Prpduct = " << prod << endl;

    return 0;
}