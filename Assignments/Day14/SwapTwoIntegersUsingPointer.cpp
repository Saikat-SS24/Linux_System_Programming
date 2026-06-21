/*swap two integers using pointers "Without using temporary variable"
*/

#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    // Let *a = 10, *b = 20
    *a = *a + *b; // *a becomes 30 (10 + 20)
    *b = *a - *b; // *b becomes 10 (30 - 20)
    *a = *a - *b; // *a becomes 20 (30 - 10)
}

int main() {
    int x = 10, y = 20;

    cout << "Before Swap: x = " << x << ", y = " << y << endl;

    swap(&x, &y);

    cout << "After Swap:  x = " << x << ", y = " << y << endl;

    return 0;
}