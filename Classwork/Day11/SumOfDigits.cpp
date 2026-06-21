/*If a Five digit number is input through the keyboard, write a program to calculate the sum of
its digits.

ex: i/p : 12345

	o/p : sum = 15
	
	explaination: 1+2+3+4+5 = 15*/

#include <iostream>
using namespace std;

int main() {
    int num = 12345;
    int originalNum = num; // Keep a copy for the final message
    int sum = 0;
    int digit;

    // Process the number until it becomes 0
    while (num > 0) {
        digit = num % 10;    // 1. Get the last digit (5, then 4, then 3...)
        sum = sum + digit;   // 2. Add it to our total
        num = num / 10;      // 3. Remove that last digit
    }

    cout << "Sum of digits of " << originalNum << " = " << sum << endl;

    return 0;
}
