/*Write a program to calculate area of circle 
taking input the radius of the circle*/

#include<iostream>
using namespace std;

int main()
{
    double radius, area;
    const double PI = 3.14159;

    cout << "Enter the radius of the circle: ";
    cin >> radius;

    area = PI * radius * radius;
    cout << "The arear of the circle with radius " << radius << " is: " << area << endl;


    return 0;
}