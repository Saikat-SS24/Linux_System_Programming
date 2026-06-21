/* Factorial using recursion */

#include <iostream>
using namespace std;

long long factorialRecursive(int n) {
    // Base case: without this, the function would run forever
    if (n <= 1) {
        return 1;
    }
    // Recursive call
    return n * factorialRecursive(n - 1);
}

int main() {
    int num = 5;
    cout << "Recursive: " << num << "! = " << factorialRecursive(num) << endl;
    return 0;
}