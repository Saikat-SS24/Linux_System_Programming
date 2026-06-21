/* Write a function to print all prime numbers in a given range */

#include <iostream>
#include <cmath> // For sqrt()

using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n < 2) return false;
    
    // Check divisors from 2 up to sqrt(n)
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false; // Found a divisor, not prime
        }
    }
    return true; // No divisors found, it's prime
}

void printPrimesInRange(int start, int end) {
    bool found = false;
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            cout << i << " ";
            found = true;
        }
    }
    
    if (!found) {
        cout << "No prime numbers found in this range.";
    }
    cout << endl;
}

int main() {
    int start, end;
    cout << "Enter start of range: ";
    cin >> start;
    cout << "Enter end of range: ";
    cin >> end;

    cout << "Prime numbers between " << start << " and " << end << " are: " << endl;
    printPrimesInRange(start, end);

    return 0;
}