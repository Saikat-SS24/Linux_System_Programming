/* Factorial using interation */

#include <iostream>
using namespace std;

long long factorialIterative(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int num = 5;
    cout << "Iterative: " << num << "! = " << factorialIterative(num) << endl;
    return 0;
}