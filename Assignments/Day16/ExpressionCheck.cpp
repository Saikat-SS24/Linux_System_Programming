/*Write a C program to check whether an expression is balanced.
Extend the logic to:
Support {} , [] , ()
Ignore characters inside quotes ( " " or ' ' )
*/

#include<iostream>
using namespace std;

int main()
{
    char expr[100];
    cout << "Enter expression: ";
    cin >> expr;

    char stack[100];
    int top = -1;
    bool isBalanced = true;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        char ch = expr[i];
        if (ch == '(' || ch == '{' || ch == '[')
        {
            top++;
            stack[top] = ch;
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (top == -1)
            {
                isBalanced = false;
                break;
            }
            char lastOpened = stack[top];
            if ((ch == ')' && lastOpened == '(') ||
               (ch == '}' && lastOpened == '{') ||
               (ch == ']' && lastOpened == '['))
            {
                top--;
            }else{
                isBalanced = false;
                break;
            }
        }
    }

    if (isBalanced && top == -1)
    {
        cout << "Balanced" << endl;
    }else{
        cout << "Not Balanced" << endl;
    }

    return 0;
}