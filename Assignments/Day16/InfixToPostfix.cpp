/*Convert an infix expression to postfix and then evaluate it using stack

Example: (3+5)*2 -> 3 5 + 2 * -> 16
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// This function evaluates a postfix string like "35+2*"
int evaluateSimple(string postfix) {
    stack<int> s;

    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        // 1. If it's a number, push it to the stack
        if (isdigit(c)) {
            // '0' is subtracted to convert ASCII char to actual integer
            s.push(c - '0');
        } 
        // 2. If it's an operator, pop two numbers and calculate
        else {
            int val2 = s.top(); s.pop(); // Top element is the second operand
            int val1 = s.top(); s.pop(); // Element below is the first operand

            switch (c) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.top();
}

int main() {
    // Example: (3+5)*2 in postfix is "35+2*"
    string postfix = "35+2*";
    
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << evaluateSimple(postfix) << endl;

    return 0;
}