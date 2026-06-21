/* The selling price & profit are entered. 
Write a program to calculate cost price of item.*/
#include<iostream>
using namespace std;

int main()
{
    double sellingPrice, profit, costPrice;
    cout << "Enter the selling price: ";
    cin >> sellingPrice;

    cout << "Enter the profit earned: ";
    cin >> profit;

    costPrice = sellingPrice - profit;
    cout << "======================" << endl;
    cout << "The cost price is: " << costPrice << endl;

    return 0;
}
