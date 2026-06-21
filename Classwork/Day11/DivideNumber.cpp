/*Write a program to Count number of ways to divide a number
 in 4 parts.

 Input Format:
 First Line Of Input Contains T test cases
 Second line of Input Contains a positive integer n,

 Output Format:
 Print the count number of ways for divison can take place.

 Examples :

 Input:
 1
   5 => 1 + 1 + 1 + 2

 Output: 1

 Input:
 1
 6
   2 + 2 + 1 + 1
   1 + 1 + 1 + 3
 Output: 2

 Input:
 
   8
 Output: 5
1+1+1+5
2+2+2+2
2+2+1+3
1+1+2+4
3+3+1+1*/


#include<iostream>
using namespace std;

int main()
{
    int n, cnt = 0;
    cout << "Enter a number: ";
    cin >> n;

    for(int i = 1; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            for(int k = j; k < n; k++)
            {
                int l = n - (i + j + k);
                if (l >= k)
                {
                    cnt++;
                    cout << i << " + " << j << "+" << k << " + " << l  << endl;
                }
            }
        }
    }

    cout << "Number of ways to divide " << n << "into 4 parts is: " << cnt << endl;
    return 0;
}