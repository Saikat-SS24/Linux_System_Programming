/*Create an ATM simulation with menu and operations*/

#include<iostream>
using namespace std;

int main()
{
    int choice;
    double balance = 1000.00;
    double amount;
    
    cout << "====Welcome to the simple ATM====" << endl;
    
    do 
    {
        cout << "\n1. Check balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option (1-4): ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                cout << "Current Balance: INR" << balance << endl;
                break;

            case 2:
                cout << "Enter deposit amount: INR";
                cin >> amount;
                balance += amount;
                cout << "Successfully deposited. New balance: INR" << balance << endl;
                break;

            case 3:
                cout << "Enter withdrawal amount: INR";
                cin >> amount;
                if (amount > balance) 
                {
                    cout << "Insufficient funds!" << endl;
                }
                else
                {
                    balance -= amount;
                    cout << "Please take your cash. Remaining balance: INR" << balance << endl;
                }
                break;

            case 4:
                cout << "Thank you for using our ATM." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again" << endl;
        }
    }
    while (choice != 4); // It is for looping until user picks 'Exit'

    return 0;
}