/* 
Operators and Control structures
Task 1B: Bit operations
Implement functions to count number of bits set in an integer, get the specific bit, set a specified bit, toggle a bit. Experiment using different types of control structures for the count operations. */

#include <iostream>
#include <bitset> // Used only for visual output of binary form

using namespace std;

/**
 * --- BIT MANIPULATION UTILITIES ---
 */

int getBit(int n, int pos) {
    return (n >> pos) & 1;
}

int setBit(int n, int pos) {
    return n | (1 << pos);
}

int clearBit(int n, int pos) {
    int mask = ~(1 << pos);
    return n & mask;
}

int toggleBit(int n, int pos) {
    return n ^ (1 << pos);
}

int countBitsFor(int n) {
    int count = 0;
    // Assuming 32-bit integer
    for (int i = 0; i < 32; i++) {
        if ((n >> i) & 1) {
            count++;
        }
    }
    return count;
}

int countBitsWhile(int n) {
    int count = 0;
    while (n > 0) {
        // This expression clears the rightmost set bit
        n = n & (n - 1);
        count++;
    }
    return count;
}

int countBitsRecursive(int n) {
    if (n == 0) return 0;
    return (n & 1) + countBitsRecursive(n >> 1);
}


int main() {
    int number = 13; 
    int position = 1;

    cout << "--- Initial State ---" << endl;
    cout << "Number: " << number << " (Binary: " << bitset<8>(number) << ")" << endl;

    cout << "\n--- Bit Operations ---" << endl;
    cout << "Bit at pos " << position << ": " << getBit(number, position) << endl;
    
    int sBit = setBit(number, 1); // 1101 -> 1111 (15)
    cout << "After setting bit 1: " << sBit << " (" << bitset<8>(sBit) << ")" << endl;

    int tBit = toggleBit(number, 2); // 1101 -> 1001 (9)
    cout << "After toggling bit 2: " << tBit << " (" << bitset<8>(tBit) << ")" << endl;

    cout << "\n--- Counting Set Bits ---" << endl;
    cout << "Using FOR loop:       " << countBitsFor(number) << endl;
    cout << "Using WHILE loop:     " << countBitsWhile(number) << endl;
    cout << "Using RECURSION:      " << countBitsRecursive(number) << endl;

    return 0;
}