/*Write a program that converts between Fahrenheit and Celsius*/

#include <iostream>
using namespace std;

int main()
{
    int choice;
    double temp, converted;

    cout << "Temperature converter" << endl;
    cout << "1. Celcius to Farenheit" << endl;
    cout << "2. Farenheit to Celcius" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter temperature in celcius: ";
        cin >> temp;
        converted = (temp * 9.0 / 5.0) + 32;
        cout << temp << "degree C is " << converted << "F" << endl;
    }
    else if (choice == 2)
    {
        cout << "Enter temperature is farenheit: ";
        cin >> temp;
        converted = (temp - 32) * 5.0 / 9.0;
        cout << temp << "F is " << converted << "C" << endl;
    }
    else{
        cout << "Invalid choice" << endl;
    }
}