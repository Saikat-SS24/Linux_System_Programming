/*The basic salary is entered. House rent allowance is 40 % of basic salary & dearness
allowance is 20% of basic salary. write a program to calculate the gross salary.*/
#include<iostream>
using namespace std;

int main()
{
    double basicSalary, hra, da , grossSalary;
    cout << "Enter the basic salary: ";
    cin >> basicSalary;

    hra = 0.4 * basicSalary;
    da = 0.2 * basicSalary;
    grossSalary = basicSalary + hra + da;

    cout << "===Salary Breakdown===" << endl;
    cout << "Basic Salary: " << basicSalary << endl;
    cout << "HRA (40%): " << hra << endl;
    cout << "DA(20%): " << da << endl;
    cout << "======================" << endl;
    cout << "Gross Salary: " << grossSalary << endl;

    return 0;
}