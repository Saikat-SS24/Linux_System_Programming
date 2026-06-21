/* Implement Fibonacci using recursion and optimize it using static memorization */

#include <iostream>
using namespace std;

long long fib(int n) {
    // 1. Create a static array to store calculated values
    // Static ensures the array persists across all recursive calls
    // Initializing with 0 (except first two) to represent "not calculated"
    static long long memo[100] = {0};

    // 2. Base Cases
    if (n <= 1) {
        return n;
    }

    // 3. Look-up: Check if we have already calculated this value
    if (memo[n] != 0) {
        return memo[n];
    }

    // 4. Store and Return: Calculate, save it in the array, then return it
    memo[n] = fib(n - 1) + fib(n - 2);
    return memo[n];
}

int main() {
    int n;
    cout << "Enter the position (N): ";
    cin >> n;

    if (n < 0 || n >= 100) {
        cout << "Please enter a number between 0 and 99." << endl;
    } else {
        cout << "Fibonacci number at position " << n << " is: " << fib(n) << endl;
    }

    return 0;
}