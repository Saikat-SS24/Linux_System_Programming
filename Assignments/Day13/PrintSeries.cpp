/*Print series 0,3,8,15,24,35,48,63,80,99*/

#include<iostream>
using namespace std;

int main()
{
    int n;
    cout << "Length of the series: ";
    cin >> n;

    cout << "The series is: ";
    for(int i = 1; i <= n; i++)
    {
        int term = (i * i) - 1;
        cout << term;
        
        if(i < n)
        {
            cout << ", ";
        }
    }
    cout << endl;
    return 0;
}