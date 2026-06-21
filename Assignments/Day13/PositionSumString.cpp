/* WAP 
1. to find sum of positions of strings "are" and "i" in the given input as a string.
2. if the strings are not found, mark their positions as -1 for each

TC_01
i/p
there are fruits in the basket
6+13 
o/p Sum = 19

TC_02
i/p
The sun is beautiful
-1+8
o/p 
Sum = 7

TC_03
i/p
We are playing football
exp: 3+11
o/p 
Sum = 14

TC_04
i/p
he works at tcs 
exp: -1+-1
o/p 
Sum = -2*/

#include<iostream>
#include<string>
using namespace std;

int main()
{
    string input;
    cout << "Enter a sentence: ";
    getline(cin, input);

    int pos1 = input.find("are");
    int pos2 = input.find("i");

    if(pos1 == string::npos)
    {
        pos1 = -1;
    }
    if(pos2 == string::npos)
    {
        pos2 = -1;
    }

    cout << "Output1: " << pos1 << " + " << pos2 << endl;
    if(pos1 != -1 && pos2 != -1)
    {
        cout << "Total Sum: " << (pos1 + pos2) << endl;
    }

    return 0;
}