/* Task 1C: Using gdb, observe memory layout of string array and integer array. Observe memory layout of single dimensional array and two dimentional array.*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    int arr1D[4] = {10, 20, 30, 40};
    int arr2D[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };


    string arrStr[2] = {"Hello", "GDB"};

    cout << "Addresses of 1D Array elements:" << endl;
    for(int i = 0; i < 4; i++) {
        cout << "arr1D[" << i << "]: " << &arr1D[i] << endl;
    }

    cout << "\nAddresses of 2D Array elements:" << endl;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "arr2D[" << i << "][" << j << "]: " << &arr2D[i][j] << endl;
        }
    }

    return 0; 
}